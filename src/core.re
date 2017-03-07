module type Component = {
  type model;
  type action;
  let init: model;
  type dispatch = action => unit;
  let update: model => action => model;
  let createElement:
    state::model =>
    dispatch::dispatch =>
    children::list ReactRe.reactElement =>
    ref::(ReactRe.reactRef => unit)? =>
    key::string? =>
    unit =>
    ReactRe.reactElement;
};

module Core (Component: Component) => {
  type store = {mutable state: Component.model};
  let store = {state: Component.init};
  let root = ReasonJs.Document.getElementById "index";
  let rec dispatch action => {
    store.state = Component.update store.state action;
    render store.state
  }
  and render state => ReactDOMRe.render <Component dispatch state /> root;
  let start _ => render store.state;
};
