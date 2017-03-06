type model = {count: int};

type action =
  | Increment
  | Decrement int;

type dispatch = action => unit;

module Counter = {
  module CounterClass = {
    include ReactRe.Component;
    let name = "Counter";
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
  include ReactRe.CreateComponent CounterClass;
  let createElement ::decBy ::state ::dispatch => wrapProps {decBy, state, dispatch};
};

let init = {count: 0};

let update state action =>
  switch action {
  | Increment => {count: state.count + 1}
  | Decrement n => {count: state.count - n}
  };

let createElement = Counter.createElement;
