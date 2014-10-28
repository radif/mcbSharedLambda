//  mcbSharedLambda.h
//
//  Created by Radif Sharafullin on 10/27/14.
//  Copyright (c) 2014 Radif Sharafullin. All rights reserved.
//

#include <iostream>
#include <memory>

#if !(__cplusplus > 201103L)
#error "this code can only be compiled in c++14 (c++1y or above)"
#endif


namespace mcb {
    template <typename T>
    struct shared_lambda{
        const std::shared_ptr<T> ptr=nullptr;
        shared_lambda(T && lambda):ptr(std::make_shared<T>(std::forward<T>(lambda))){}
        T& get() const{return *ptr;}
        template <typename... Args> decltype(auto) operator() (Args&& ...args) const{return (*ptr)(std::forward<Args>(args)...);}
    };
    template <typename T>
    shared_lambda<T> make_shared_lambda(T && lambda){
        return shared_lambda<T>(shared_lambda<T>(std::move(lambda)));
    }
}

/*
 Example:
 int i=0;
 auto myHeapLambda1(mcb::make_shared_lambda([=]() mutable{
 i++;
 printf("%i\n", i);
 }));
 auto myHeapLambda2(mcb::make_shared_lambda([=](int step) mutable{
 i+=step;
 printf("%i\n", i);
 }));
 
 auto myHeapLambda3(mcb::make_shared_lambda([=](int addition){
 return addition+22;
 }));
 
 auto myHeapLambda44=myHeapLambda1;
 myHeapLambda44();
 myHeapLambda44();
 myHeapLambda1();
 
 myHeapLambda2(2);
 myHeapLambda2(2);
 myHeapLambda2(2);
 
 int j=myHeapLambda3(22);
 printf("%i\n", j);
 
 */