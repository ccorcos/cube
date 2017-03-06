module type Component = {
  type model;
  type action;
  let init: model;
  let update: model => action => model;
  let createElement: 'view;
};

module Core (Component: Component) => {
  type store = {mutable state: Component.model};
  let store = {state: Component.init};
  let root = ReasonJs.Document.getElementById "index";
  let rec dispatch action => {
    store.state = Component.update store.state action;
    render store.state
  }
  and render state => ReactDOMRe.render <Component dispatch state decBy=2 /> root;
  let start _ => render store.state;
};

module App = Core Counter;
