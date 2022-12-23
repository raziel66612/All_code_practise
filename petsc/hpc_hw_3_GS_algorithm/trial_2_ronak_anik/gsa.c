
#include "petsc.h"
#include "petscvec.h"


static char help[] = "\n\n This code take k vectors of size N and check thier orthogonality by gram scmidt algorithm \n\n";


int main(int argc,char **args)
{
PetscErrorCode ierr;
PetscInt i,j; // number of vectors
PetscInt k=20,n=1000;
Vec y[k];
PetscRandom    rann;
PetscReal      dot_prod,normV;
PetscLogEvent  evnt;
PetscBool flg;

    PetscInitialize(&argc,&args,NULL,help);

ierr= PetscOptionsGetInt(PETSC_NULL,PETSC_NULL,"-k",&k,&flg); CHKERRQ(ierr);
ierr= PetscOptionsGetInt(PETSC_NULL,PETSC_NULL,"-n",&n,&flg); CHKERRQ(ierr);


ierr = PetscRandomCreate(PETSC_COMM_WORLD,&rann);CHKERRQ(ierr);
ierr = PetscRandomSetFromOptions(rann);CHKERRQ(ierr);

// for (i=0; i<k; i++) { // create k vectors
//     ierr = VecCreate(PETSC_COMM_WORLD,&y[i]);CHKERRQ(ierr);
//     ierr = VecSetSizes(y[i],PETSC_DECIDE,n);CHKERRQ(ierr);
//     ierr = VecSetFromOptions(y[i]);CHKERRQ(ierr);
//     ierr = VecSetRandom(y[i],rann);CHKERRQ(ierr);
// }
// ierr = PetscRandomDestroy(&rann);CHKERRQ(ierr); 
   
ierr = VecCreate(PETSC_COMM_WORLD,&y[0]);CHKERRQ(ierr);
ierr = VecSetSizes(y[0],PETSC_DETERMINE,n);CHKERRQ(ierr);
ierr = VecSetFromOptions(y[0]);CHKERRQ(ierr);
for (i=1; i<k; ++i) { // create k vectors
    ierr = VecDuplicate(y[0], &y[i]);CHKERRQ(ierr);
}

  for (i = 0; i < k; ++i) {
    ierr = VecSetRandom(y[i], rann);CHKERRQ(ierr);
}

ierr = PetscRandomDestroy(&rann);CHKERRQ(ierr); 



// ------------------log ------

    ierr = PetscLogEventRegister("Gram_Schmidt_orthogonalization",0,&evnt);CHKERRQ(ierr);  // log evnt
    ierr = PetscLogEventBegin(evnt,0,0,0,0);CHKERRQ(ierr);
//--------------------- orthogonalize the vectors ----------------------
for (i=0; i<k; i++) {
    for (j=0; j<i; j++) {
        ierr = VecDot(y[i],y[j],&dot_prod);CHKERRQ(ierr);
        ierr = VecAXPY(y[i],-dot_prod,y[j]);CHKERRQ(ierr);
    }
    ierr = VecNorm(y[i],NORM_2,&normV);CHKERRQ(ierr);
    ierr = VecScale(y[i],1.0/normV);CHKERRQ(ierr);
}
ierr = PetscLogEventEnd(evnt,0,0,0,0);CHKERRQ(ierr);


// -------print dot product of vect on terminal to verify orthogonality ----------------
    for (i=0; i<k; i++) {
        for (j=0; j<k; j++) {
            PetscScalar dot;
            ierr = VecDot(y[i],y[j],&dot) ;CHKERRQ(ierr);
            if(PetscAbsScalar(dot)< 0.00001) dot=0.0;
            ierr = PetscPrintf(PETSC_COMM_WORLD,"%.1g ",dot) ;CHKERRQ(ierr);
            }
        ierr = PetscPrintf(PETSC_COMM_WORLD, "\n");CHKERRQ(ierr);
        }
   
    for (i=0; i<k; i++) {
        ierr = VecDestroy(&y[i]);CHKERRQ(ierr);
    }
    ierr = PetscFinalize();
    return 0;
}