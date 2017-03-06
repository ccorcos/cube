/* We want some type constraints on the root component */
module type CoreComponent = {
  type model;
  let init: model;
  type action;
  let update: state::model => action::action => model;
  /* Ideally, we could also enforce the props accepting a dispatch and state */
};

module Core (Comp: CoreComponent) => {
  /* We want state to be mutable and dispatch to update it */
  let state = Comp.init;
  let dispatch action => Comp.update ::state ::action;
  /* Need to somehow merge props */
  let start props root = ReactDOMRe.render <Comp dispatch action {...props} /> root;
};

/* Counter top-level module and Counter componet module are different. */
let app = Core Counter;
let root = ReasonJs.Document.getElementById "index";
app.start {decBy: 10} root;
