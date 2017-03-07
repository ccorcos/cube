module type CounterProps = {let decBy: int;};

module Counter (Props: CounterProps) => {
  type model = {count: int};
  type action =
    | Increment
    | Decrement int;
  type dispatch = action => unit;
  let init = {count: 0};
  let update state action =>
    switch action {
    | Increment => {count: state.count + 1}
    | Decrement n => {count: state.count - n}
    };
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
    let render {props, updater} => {
      Js.log "render Counter";
      <div>
        <button onClick=(updater dec)> (ReactRe.stringToElement "-") </button>
        <span> (ReactRe.stringToElement (string_of_int props.state.count)) </span>
        <button onClick=(updater inc)> (ReactRe.stringToElement "+") </button>
      </div>
    };
  };
  include ReactRe.CreateComponent CounterClass;
  let createElement ::state ::dispatch => wrapProps {decBy: Props.decBy, state, dispatch};
};
