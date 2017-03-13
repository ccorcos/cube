/* TODO this should belong in Reason and should be typed out */
external getBoundingClientRect : ReasonJs.Document.element => 'fuckit =
  "getBoundingClientRect" [@@bs.send];

/* TODO add types for `pageX` and `pageY` on event. Should be int, not float. */
let getMouse event => {
  let rect = getBoundingClientRect event##currentTarget;
  ((event##pageX -. rect##left) /. Defs.size, (event##pageY -. rect##top) /. Defs.size)
};
