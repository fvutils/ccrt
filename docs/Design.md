
- Use Var<> and RandVar<> to declare solver variables

- Composite objects derive from RandObj

- Var/RandVar instances should pass a name to the constructor

- RandObj-derived objects must pass 'this' to base constructor

- Concerned about mixed hierarchy
  - Randomized class contains a handle which should be independently randomized
  - This should be an anonymous 'RandVar' to create an independent scope
  - Var doesn't support no-arg constructor, since it is always used inside an existing scope
 
``` 
class MyClass : RandObj {
public:
  MyClass(const RandObjCtor &scope) : RandObj(this) { }
  
  // Independently-randomized variable
  RandVar<MyRandObj>      rand_var;
  - 
};
```

# Requirements
*- Support integral fields (bool and 8, 16, 32, 64 bits / signed and unsigned)
*- Support constraint blocks that have statement-like semantics 
  (avoid chaining with comma)
*- Support constraint overrides using inheritance
*- Support procedural override of constraint blocks

- Support composite fields
- Support inline constraints (?)

# Constraints
  * ``==`` (x)
  * ``!=`` (x)
  * ``+`` (x)
  * ``-`` (x)
  * ``/``
  * ``*``
  * ``%``
  * ``&`` (x)
  * ``|`` (x)
  * ``&&`` (x)
  * ``||`` (x)
  * ``!`` (x)
  * ``~`` (x)
  * ``<`` (x)
  * ``<=`` (x)
  * ``>`` (x)
  * ``>=`` (x)
  * if/else (x)
  * implies (x)
  * in
  * part select (x)

# Expression Tree

We need expressions for two reasons:
- Create constraints
- Query the value of expressions being covered

# Construction approach
- Build variables as we go
- Build applicable constraint blocks once the entire root object is constructed
  - Cannot really reference fields until later

# Coverage Model

- A CoverpointBinCollectionModel holds a set of coverpoint bin models (is this really just a coverpoint?)
  - Each ICoverpointBinModel can independently have a hit on each sample
  - Each ICoverpointBinModel has >=1 bin

- Types of ICoverpointBinModel:
  - CoverpointSingleBinModel -- bin with a collection of ranges that describe the bin
  - CoverpointMultiBinModel -- bin with a collection of single bin models
  - CoverpointArrayBinModel -- bin with a linear array of bins

- Each coverpoint holds a set of bin collections, which are named
- Each coverpoint holds a vector of pointers to the bins in the bin collections
  that are sorted in 
- Each coverpoint holds two maps: unhit bins, and unreachable bins
-> The keys to these maps are an index into the bin-collection vector
-> Initially, the unreachable bins map is empty and the unhit bins map is fully populated
- Each sample must search this set to determine 
- Each bin collection maintains information on hit, unhit, and illegal bins




