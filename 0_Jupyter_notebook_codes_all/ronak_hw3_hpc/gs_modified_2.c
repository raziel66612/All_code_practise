// Write a serial PETSc program to orthogonalize a set of vectors using the GramSchmidt process
// using the Classical variant (CGS).
// Use VecSetRandom() to set the vector values.
// Check that the output vectors are orthogonal in the code.
// use PetscLogEventRegister() to create a logging event, PetscLogEventBegin()/PetscLogEventEnd() to time the code, and -log_view to output the timing.

#include "petsc.h"
#include "petscvec.h"

int main(int argc,char **args)
{
    PetscErrorCode ierr;
    PetscInt       i,j,n=64; // number of vectors
    PetscScalar    *array;
    Vec            x[n],y[n];
    PetscRandom    rctx;
    PetscReal      norm;
    PetscLogEvent  event;

    PetscInitialize(&argc,&args,(char*)0,0);
    ierr = PetscRandomCreate(PETSC_COMM_WORLD,&rctx);CHKERRQ(ierr);
    ierr = PetscRandomSetFromOptions(rctx);CHKERRQ(ierr);
    for (i=0; i<n; i++) { // create n vectors
        ierr = VecCreate(PETSC_COMM_WORLD,&x[i]);CHKERRQ(ierr);
        ierr = VecSetSizes(x[i],PETSC_DECIDE,50000);CHKERRQ(ierr);
        ierr = VecSetFromOptions(x[i]);CHKERRQ(ierr);
        ierr = VecSetRandom(x[i],rctx);CHKERRQ(ierr);
        ierr = VecDuplicate(x[i],&y[i]);CHKERRQ(ierr);
    }
    ierr = PetscRandomDestroy(&rctx);CHKERRQ(ierr); // destroy random context

    // register a logging event
    ierr = PetscLogEventRegister("GramSchmidt",0,&event);CHKERRQ(ierr);
    ierr = PetscLogEventBegin(event,0,0,0,0);CHKERRQ(ierr);
    // orthogonalize the vectors
    for (i=0; i<n; i++) {
        ierr = VecCopy(x[i],y[i]);CHKERRQ(ierr);
        for (j=0; j<i; j++) {
            ierr = VecDot(y[i],y[j],&norm);CHKERRQ(ierr);
            ierr = VecAXPY(y[i],-norm,y[j]);CHKERRQ(ierr);
        }
        ierr = VecNorm(y[i],NORM_2,&norm);CHKERRQ(ierr);
        ierr = VecScale(y[i],1.0/norm);CHKERRQ(ierr);
    }
    ierr = PetscLogEventEnd(event,0,0,0,0);CHKERRQ(ierr);

    // check that the vectors are orthogonal
    // for (i=0; i<n; i++) {
    //     for (j=0; j<i; j++) {
    //         ierr = VecDot(y[i],y[j],&norm);CHKERRQ(ierr);
    //         if (norm > 1e-10) {
    //             ierr = PetscPrintf(PETSC_COMM_WORLD,"Vectors %d and %d are not orthogonal (norm=%g)", i, j, norm);CHKERRQ(ierr);
    //         }
    //     }
    // }

    // destroy vectors
    for (i=0; i<n; i++) {
        ierr = VecDestroy(&x[i]);CHKERRQ(ierr);
        ierr = VecDestroy(&y[i]);CHKERRQ(ierr);
    }
    ierr = PetscFinalize();
    return 0;
}