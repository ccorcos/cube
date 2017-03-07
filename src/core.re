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

/* Wiring everything up outside of a top-level React component. I don't suggest using this, but I'm going to leave it here because its an interesting example of in-place mutation. */
module CoreApp (Component: Component) => {
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

module Core = {
  module CoreClass = {
    include ReactRe.Component.Stateful;
    let name = "Core";
    type model;
    type action;
    type update = model => action => model;
    type dispatch = action => unit;
    type props = {init: model, update, render: dispatch => model => ReactRe.reactElement};
    type state = model;
    let getInitialState props => props.init;
    let dispatch {props, state} action => Some (props.update state action);
    let render {props, state, updater} => props.render (updater dispatch) state;
  };
  include ReactRe.CreateComponent CoreClass;
  let createElement ::init ::update ::render => wrapProps {init, update, render};
};
