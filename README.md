# Disadvantages of the original code.

#### 1. Using single class `Feature` to model all kinds of Features.
Storing the kind of Feature in a member variable, and `switch`-ing on it is, in essence, another way of implementing polymorphism. C++ provides special tools for that: dynamic dispatch for member functions, and function overloading and function templates for class clients.

The disadvantages of using single class `Feature` to model all kinds of Features are: 
1. The fact that class `Feature` does not model a single concept is a disadvantage by itself.
2. The `Feature` member functions don't do one thing. They do different things depending on the `Feature`'s "dynamic type". The logic, related to all Features, is mixed up, and each function becomes overcomplicated.
3. The clients of `Feature` are also forced to cumulate the logic, related to each kind of Feature, in one function. 
4. Adding, removing, or modifying the behavior of one Feature requires to change the code in many places. Adding or removing a Feature requires to *change* the client functions, instead of adding/removing the overloads.
5. Unit testing is extremely impeded.
6. Impossible to design a proper class interface. E.g.: some Features have vertices, and for them it's reasonable to provide `getVertex` method, whereas it would be invalid for other Features like Circle or Ellipse.
7. Impossible to design a proper class representation: the set of necessary member variables is different for Circle, Square, Triangle, etc. 
8. Easy to create invalid states. 
 
#### 2. Responsibilities of `Feature`.
Drawing a `Feature` should not be a responsibility of `Feature`. Neither is reading from a file. One should clearly distinguish between *actions to be done with* an object and *actions to be done by* an object. Thus, a `Feature` might need to be drawn in different ways depending on the context, and it's up to the client to decide.

Moreover, putting drawing logic into the `Feature` class will make `Feature` to depend on the graphics system. Instead, Features should implement the abstraction on which the graphics system depends (e.g. provide the set of lines and vertices they consist of).

#### 3. Enabling invalid states.
Enabling existence of objects in invalid states overcomplicates the code, as the clients always need to call `Feature::isValid()`. Validity should be checked during the construction. One may consider `throw`ing from the constructor, or returning `optional<Feature>` from the factory.

#### 4. Text file format.
The kind of `Feature` should not be encoded by the number of values, required to store its state, as this can lead to ambiguities. The text file should be human-readable, and the best is to identify `Feature`s by names. If the file does not need to be human-readable, then there is also no reason to store the data in plain text. 

#### 5. Using `enum`.
If really necessary, rather use `enum class`, as `enum` allows implicit conversions and leaks the identifiers outside of its scope. 

#### 6. Using raw pointer as an array.
The main disadvantages of ~~plain arrays~~ raw-ponters-to-preallocated-memory-blocks are that they don't enforce bound-checking, and don't guarantee correct memory allocation/deallocation. The standard containers (`std::vector`) are free of these shortcomings, and  in addition provide basic functionality, are compatible with standard algorithms (`<algorithm>`), and enable using custom allocators. 

#### 7. Using `stdio.h`
The utilities in `stdio.h` are not memory-safe, not exception-safe, not type-safe, do not comply with RAII (`FILE`s must be explicitly closed with `fclose`), do not support different encodings, and are a subject of *Uncontrolled format string* vulnerability. Unit-testing functions accepting FILE* require a FILE mock. 

`iostream` is ~~free of the above disadvantages~~ much better in the above respects. It provides higher level abstractions (locales, custom streaming operators, streams that can represent a file, a string, or an object generating the data on-the-fly). 

#### Excellent collection of antipatterns!
