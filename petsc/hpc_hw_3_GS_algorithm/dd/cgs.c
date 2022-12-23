
#include <petsc.h>


static PetscErrorCode CGS(PetscInt k, Vec va[], Vec *vq[])
{
  PetscReal      norm;
  PetscInt       i, j;
  PetscErrorCode ierr;

  PetscFunctionBegin;
  ierr = PetscMalloc1(k, vq);CHKERRQ(ierr);
  for (i = 0; i < k; ++i) {ierr = VecDuplicate(va[0], &(*vq)[i]);CHKERRQ(ierr);}
  for (i = 0; i < k; ++i) {
    ierr = VecCopy(va[i], (*vq)[i]);CHKERRQ(ierr);
    for (j = 0; j < i; ++j) {
      PetscScalar dot;

      ierr = VecDot((va)[i],(*vq)[j], &dot);CHKERRQ(ierr);
      ierr = VecAXPY((*vq)[i], -dot, (*vq)[j]);CHKERRQ(ierr);
    }
    ierr = VecNorm((*vq)[i], NORM_2, &norm);CHKERRQ(ierr);
    ierr = VecScale((*vq)[i], 1./norm);CHKERRQ(ierr);
  }
  PetscFunctionReturn(0);
}



int main(int argc, char **argv)
{
  Vec           *va, *vq;
  PetscRandom    r;
  PetscInt       k = 64, N = 50000, i, j;
  PetscErrorCode ierr;

  ierr = PetscInitialize(&argc, &argv, NULL, NULL);if (ierr) return ierr;
  ierr = PetscOptionsGetInt(NULL, NULL, "-N", &N, NULL);CHKERRQ(ierr);
  ierr = PetscOptionsGetInt(NULL, NULL, "-k", &k, NULL);CHKERRQ(ierr);

  ierr = PetscMalloc1(k, &va);CHKERRQ(ierr);
  ierr = VecCreate(PETSC_COMM_WORLD, &va[0]);CHKERRQ(ierr);
  ierr = VecSetSizes(va[0], PETSC_DETERMINE, N);CHKERRQ(ierr);
  ierr = VecSetFromOptions(va[0]);CHKERRQ(ierr);
  for (i = 1; i < k; ++i) {
    ierr = VecDuplicate(va[0], &va[i]);CHKERRQ(ierr);
  }

  ierr = PetscRandomCreate(PETSC_COMM_WORLD, &r);CHKERRQ(ierr);
  ierr = PetscRandomSetType(r, PETSCRAND48);CHKERRQ(ierr);
  for (i = 0; i < k; ++i) {
    ierr = VecSetRandom(va[i], r);CHKERRQ(ierr);
    ierr = VecViewFromOptions(va[i], NULL, "-a_view");CHKERRQ(ierr);
  }
  ierr = PetscRandomDestroy(&r);CHKERRQ(ierr);

  ierr = CGS(k, va, &vq);CHKERRQ(ierr);
  for (i = 0; i < k; ++i) {ierr = VecDestroy(&va[i]);CHKERRQ(ierr);}
  ierr = PetscFree(va);CHKERRQ(ierr);

  /* Check orthogonality of the GS basis, should produce the identity matrix */
  ierr = PetscPrintf(PETSC_COMM_WORLD, "This should be the identity matrix\n");CHKERRQ(ierr);
  for (i = 0; i < k; ++i) {
    for (j = 0; j < k; ++j) {
      PetscScalar dot;

      ierr = VecDot(vq[i], vq[j], &dot);CHKERRQ(ierr);
      if (PetscAbsScalar(dot) < PETSC_SMALL) dot = 0.;
      ierr = PetscPrintf(PETSC_COMM_WORLD, "%.2g ", dot);CHKERRQ(ierr);
    }
    ierr = PetscPrintf(PETSC_COMM_WORLD, "\n");CHKERRQ(ierr);
  }

  for (i = 0; i < k; ++i) {
    ierr = VecViewFromOptions(vq[i], NULL, "-q_view");CHKERRQ(ierr);
    ierr = VecDestroy(&vq[i]);CHKERRQ(ierr);
  }
  ierr = PetscFree(vq);CHKERRQ(ierr);
  ierr = PetscFinalize();
  return ierr;
}
