
//          Copyright Oliver Kowalke 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <cstdlib>
#include <iostream>
#include <memory>

#include <boost/context/all.hpp>

#define yield(x) p=x; mctx();

int main() {
    int n=35;
    int p=0;
    boost::context::execution_context mctx( boost::context::execution_context::current() );
    boost::context::execution_context ctx(
        [n,&p,&mctx](void*)mutable{
            int a=0;
            int b=1;
            while(n-->0){
                yield(a);
                auto next=a+b;
                a=b;
                b=next;
            }
        });
    for(int i=0;i<10;++i){
        ctx();
        std::cout<<p<<" ";
    }
    std::cout<<std::endl;

    std::cout << "main: done" << std::endl;
}
