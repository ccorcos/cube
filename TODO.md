# To Do

- re-implement cube
- webpack dev server with htmlplugin
- typesafe inline styles


## Questions

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
