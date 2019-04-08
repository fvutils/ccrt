
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
