# STLLab

Implement a tiny STL in C++11.

## Use

A lab to implement STL.

It is recommended that you compare the [sigstl](http://www.rrsd.com/software_development/stl/stl/download.html) and [stlport](https://sourceforge.net/projects/stlport/files/) implementations.

You can watch [this video](https://www.youtube.com/watch?v=Edcwv38c7d4&list=PLTcwR9j5y6W2Bf4S-qi0HBQlHXQVFoJrP) and [this book](https://union-click.jd.com/jdc?e=&p=JF8BAM8JK1olXDYCVFdeCEwXA19MRANLAjZbERscSkAJHTdNTwcKBlMdBgABFksXCmwIHFsVQl9HCANtf0NEdGtVHQZ1I14GCR0jSTRES218e1cZbQMCVV9aDU0TA2g4GFoWWAYEUF1bCHsnA244TTUVXAcDVV5aDEwSM244G1wQWAILVF5dCEMVAl8IE18libKwgs3L0cSY1cqMz8e0iaK1gOXNOHsnAF84K1slXjZcOl8OCEtCAG0MdQFeBVMHFwwAZksQAWwBGVgUVTYAVV9fCns).

The following presentation shows the file you will implement and the corresponding test file, and you can modify the `test/cppuint/cppunit_unitl.h` file and `CMakeLists.txt` to open the corresponding test file.

> Note the these file have the same names as the corresponding file in the two source implementations for your reference.

**The most important thing is to understand generic programming.**

## labs 

* `stl_allocator` memory management, imitating `sigstl` , implementing memory pools.
  * File:  `src/stl_alloc.h`
  * Test:  `test/allocator_test.cpp`
  
* `auto_ptr`  implementing the simplest smart pointer.
  * File: `src/memory.h`
  * Test: `test/memory_test.cpp`
  
* `type_traits` getting started whit the concept of  generic procgramming.
  * File: `src/type_traits.h`
  * Test: `test/type_traits_test.cpp`
  
* global constructor and destructor 
  * File: `src/stl_construct.h`
  
* `iterator_traits`  base iterator
  
  * File: `src/stl_iterator_base.h`
  
* [algorithm function] -> copy & fill function `iterator` + `type_traits`  generic programming 
  * File: `src/stl_algobase.h`
  
* `uninitialized_[copy/fill/fill_n]`,  copy/fill + constructor
  * File: `src/stl_uninitialized.h`
  
* `_Alloc_traits`  encapsulation provides a uniform interface to cccontainers for both allocators that need to be instantiated and those that do not.

  * File: `src/stl_alloc.h`

  * > This is not in the book&video,  you need to look at the code to understand it yourself. You can implement it once for echo container, like in `sgistl`, [or you can implement a unified interface, which is how i did it](https://github.com/wlingze/TinySTL/blob/dev/src/stl_alloc.h#L484).

* `iterator` for the simple iterator is wrapped again, mainly the implementation of the reverse iterator.

  * File: `src/stl_iterator.h`

* `vector`  **First container!!!**  

  * File: `src/stl_vector.h`
  * Test: `test/vector_test.h` 




## TODO

- [ ] `list`
- [ ] `hash_map` / `hash_set`
- [ ] `tree`

## Reference

* [sigstl](http://www.rrsd.com/software_development/stl/stl/download.html)
* [stlport](https://sourceforge.net/projects/stlport/files/)

