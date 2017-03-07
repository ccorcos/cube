let rec firstN n l =>
  if (n === 0 || List.length l === 0) {
    []
  } else {
    let h = List.hd l;
    let t = List.tl l;
    List.append [h] (firstN (n - 1) t)
  };

module Undoable (Component: Core.Component) => {
  /* State */
  type model = {time: int, states: list Component.model};
  let init = {time: 0, states: [Component.init]};
  /* Action */
  type action =
    | Undo
    | Redo
    | Child Component.action;
  type dispatch = action => unit;
  /* Update */
  let update state action => {
    let {time, states} = state;
    switch action {
    | Undo => {states, time: time - 1}
    | Redo => {states, time: time + 1}
    | Child a => {
        time: time + 1,
        states: {
          let currentState = List.nth states time;
          let nextState = Component.update currentState a;
          let history = firstN (time + 1) states;
          List.append history [nextState]
        }
      }
    }
  };
  /* View */
  module UndoableClass = {
    include ReactRe.Component;
    let name = "Undoable";
    type props = {state: model, dispatch};
    let undo {props} _ => {
      props.dispatch Undo;
      None
    };
    let redo {props} _ => {
      props.dispatch Redo;
      None
    };
    let child {props} a => {
      props.dispatch (Child a);
      None
    };
    let render {props, updater} => {
      let {time, states} = props.state;
      let canUndo = time > 0;
      let canRedo = time < List.length states - 1;
      <div>
        <button onClick=(updater undo) disabled=(Js.Boolean.to_js_boolean (not canUndo))>
          (ReactRe.stringToElement "undo")
        </button>
        <button onClick=(updater redo) disabled=(Js.Boolean.to_js_boolean (not canRedo))>
          (ReactRe.stringToElement "redo")
        </button>
        <Component state=(List.nth states time) dispatch=(updater child) />
      </div>
    };
  };
  include ReactRe.CreateComponent UndoableClass;
  let createElement ::state ::dispatch => wrapProps {state, dispatch};
};
