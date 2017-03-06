# To Do

- seems like `memoizedUpdaterCount` is unused and we instead use `maxMemoizedCount` when we make the array. https://github.com/reasonml/rehydrate/blob/06c409d3fb6334f79cd1e8b9d9916bd8d3d80e84/src/reactRe.re#L282

- if `createElement` is just partially applying `wrapProps`, then why do we even have it?

- what if `instanceVars` weren't mutable and were instead returned from functions the same way state works with the updater and lifecycle methods? seems like we could have a returnBag in the same sense that we have a componentBag for updating the component in a functional style. the only funky thing here is we can destructure what we want out of the componentBag, but we have to write out the entire returnBag every time.

- where can I read about Obj.magic, Js.Null.return?

- is it possible to define polymorphic functions?





- re-implement cube
- webpack dev server with htmlplugin
- typesafe inline styles


## Questions

- publishing packages
- utility packages
