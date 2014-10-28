mcbSharedLambda
===============

Inspired by swift blocks, a convenient wrapper for c++14 to create/pass and hold the lambda on the heap.

By default the lambda litteral syntax will create it on the stack, means it has to be copied around and won't share the state (mutable lambdas) once leaves the stack. In order to create and call lambdas on the heap one needs to use a clunky syntax of shared_ptr.

With mcbSharedLambda, you can create the heap lambdas as follows:

	
	//to create:
	auto mySharedLambda(mcb::make_shared_lambda([](...){...}));
	
	//to call
	mySharedLambda();
	
	//to pass to another variable (lambda itself won't copy, just wrapper):
	auto anotherPointerToTheSameSharedLambda(mySharedLambda);
	
	//to get by ref:
	auto & regularLambdaAsReference(anotherPointerToTheSameSharedLambda.get());
	
	//to copy:
	auto myCopiedSharedLambda(mcb::make_shared_lambda(anotherPointerToTheSameSharedLambda.get()));
	auto regularLambdaAsCopy(anotherPointerToTheSameSharedLambda.get());


assignment operator or passing to a function won't duplicate the lambda itself, but a wrapper. Internally lambda pointer is swapped inside std::shared_ptr which takes care of the automatic memory management.

Lambdas on the heap can:
1. count the times it was called or keep other state info via captured vars (as do something once 2 async callbacks received)
2. be passed as arguments without being copied.
3. called directly just as regular lambda
