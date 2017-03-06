module type Component = {
  type model;
  let init: model;
  type action;
  let update: model => action => model;
  let createElement: 'view;
};

module TwoOf (Component: Component) => {
  type model = {one: Component.model, two: Component.model};
  type action =
    | One Component.action
    | Two Component.action;
  type dispatch = action => unit;
  module TwoOfComponent = {
    module TwoOfClass = {
      include ReactRe.Component;
      let name = "TwoOf";
      type props = {state: model, dispatch};
      let one {props} action => {
        props.dispatch (One action);
        None
      };
      let two {props} action => {
        props.dispatch (Two action);
        None
      };
      let render {props, updater} =>
        <div>
          <Component dispatch=(updater one) state=props.state.one />
          <Component dispatch=(updater two) state=props.state.two />
        </div>;
    };
    include ReactRe.CreateComponent TwoOfClass;
    let createElement ::state ::dispatch => wrapProps {state, dispatch};
  };
  let init = {one: Component.init, two: Component.init};
  let update state action =>
    switch action {
    | One a => {...state, one: Component.update state.one a}
    | Two a => {...state, two: Component.update state.two a}
    };
  let createElement = Counter.createElement;
};
