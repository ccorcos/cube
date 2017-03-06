/* This is meant to be a simple stateless counter with a Redux-/Elm-/PureScript-like architecture. */
module Counter = {
  include ReactRe.Component;
  let name = "Counter";
  /* The state model of this component along with the initial state. */
  type model = {count: int};
  let init = {count: 0};
  /* Using Variants to encode actions is really clean. */
  type action =
    | Increment
    | Decrement int;
  /* Update the state model */
  let update ::state ::action =>
    switch action {
    | Increment => {count: state.count + 1}
    | Decrement n => {count: state.count - n}
    };
  /* Dispatching actions */
  type dispatch = action => unit;
  type props = {decBy: int, state: model, dispatch};
  let inc {props} _ => {
    props.dispatch Increment;
    None
  };
  let dec {props} _ => {
    props.dispatch (Decrement props.decBy);
    None
  };
  let render {props, updater} =>
    <div>
      <button onClick=(updater dec)> (ReactRe.stringToElement "-") </button>
      <span> (ReactRe.stringToElement (string_of_int props.state.count)) </span>
      <button onClick=(updater inc)> (ReactRe.stringToElement "+") </button>
    </div>;
};

include ReactRe.CreateComponent Counter;

let createElement ::decBy ::state ::dispatch => wrapProps {decBy, state, dispatch};
