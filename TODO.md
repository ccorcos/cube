# To Do

- refactor the elmish examples
- explain types in the readme
- look at other examples

abstract types (type model) vs generic types (type 'model)
wait, whats a polymorphic type?
_ and unit types?

a polymorphic type would be a variant
type a = | Int int | Str string

`'a`  simply means "I don't know the type - figure it out"

So naturally, when defining polymorphic functions, if you leave the types as 'a, it will figure out that it is polymorphic. You can then ensure that it's polymorphic by actually requiring polymorphism using 'a .


let foo (x : 'a) => Js.log "wow";

foo 1;

foo "a";

compiles

- Intro to Reason Article
  - How to install and setup the IDE?
  - Which docs to read and what to pay attention to?
  - How to make a simple app?
  - How to build a composable Elm-like app?
http://codepen.io/ccorcos/pen/jrxbXA?editors=0010


let rec firstN n l =>
  if (n === 0 || List.length l === 0) {
    []
  } else {
    let h = List.hd l;
    let t = List.tl l;
    List.append [h] (firstN (n - 1) t)
  };

let rec firstN n l =>
  switch (n, l) {
  | (0, _) => []
  | (_, []) => []
  | (n, [h, ...t]) => List.append [h] (firstN (n - 1) t)
  };


[%bs.debugger] compiles to debugger


try (Some (List.hd my_list)) {
| Not_found exn => None
};


https://github.com/rickyvetter/rehydrate/tree/redux/examples/redux
https://github.com/OvermindDL1/bucklescript-tea/tree/master/src
https://github.com/reasonml/rehydrate/blob/master/documentation.md#component-api


- re-implement cube
- webpack dev server with htmlplugin
- typesafe inline styles


## Questions

- polymorphic functions.
- list cons patern match.

(3) what if `instanceVars` weren't mutable and were instead returned from functions the same way state works with the updater and lifecycle methods? seems like we could have a returnBag in the same sense that we have a componentBag for updating the component in a functional style. the only funky thing here is we can destructure what we want out of the componentBag, but we have to write out the entire returnBag every time.

- seems like `memoizedUpdaterCount` is unused and we instead use `maxMemoizedCount` when we make the array. https://github.com/reasonml/rehydrate/blob/06c409d3fb6334f79cd1e8b9d9916bd8d3d80e84/src/reactRe.re#L282

- where can I read about Obj.magic, Js.Null.return?

- is it possible to define polymorphic functions?

- let mutable variable

- counter problem

- some basic tooling for building a blog
  - i need to load markdown files from the filesystem. should I do this from markdown? or should I generate Reason files on the fly with a makefile? should I use webpack?
  - how can i codesplit and asynchronously modules separately?


- publishing packages
- utility packages
