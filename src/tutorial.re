/* Lets create the simplest possible component. Remember a module is a file. If I put everything in this module in a file named `simplest.re` then it would be literally the same thing except I could use it globally from any other file. */
module Simplest = {
  module Component = {
    /* include pulls a bunch of functions and variables into this module scope */
    include ReactRe.Component;
    let name = "Simplest";
    /* `unit` is the type for () which is like null or undefined */
    type props = unit;
    /* the _ means we dont care about it */
    let render _ => <div> (ReactRe.stringToElement "hello world") </div>;
  };
  include ReactRe.CreateComponent Component;
  /* when JSX transpiles, it calls `createElement` so we need to define that ourselves using the `wrapProps` to handle all the curried arguments that the React internals use. since this component doesn't have any props, it's rather unexciting */
  let createElement = wrapProps ();
};

/* If we want to spend props, we need to set the type and a labelled argument to createElement */
module SimpleWithProps = {
  module Component = {
    include ReactRe.Component;
    let name = "Simplest";
    type props = {who: string};
    /* we can just destructure `props` out of the componentBag */
    let render {props} => <div> (ReactRe.stringToElement ("hello " ^ props.who)) </div>;
  };
  include ReactRe.CreateComponent Component;
  /* here, we to convert labeled arguments into the props record */
  let createElement ::who => wrapProps {who: who};
};

/* Children are represented as a list and need to be typed as well. */
module SimpleWrapper = {
  module Component = {
    include ReactRe.Component;
    let name = "SimpleWrapper";
    type props = {children: list ReactRe.reactElement};
    /* HERE style  */
    let render {props} =>
      <div style={"color": "red"}> (ReactRe.arrayToElement (Array.of_list props.children)) </div>;
  };
  include ReactRe.CreateComponent Component;
  let createElement ::children => wrapProps {children: children} ::children;
};

/* Now we're going to define a stateful component */
module Counter = {
  module Component = {
    include ReactRe.Component.Stateful;
    let name = "Counter";
    type props = unit;
    type state = {count: int};
    let getInitialState _ => {count: 0};
    /* these handlers get a `componentBag` and an `event`, and they return an `option state` obviating the need to ever call `setState` */
    let inc {state} _ => Some {count: state.count + 1};
    let dec {state} _ => Some {count: state.count - 1};
    /* updater will memoize function references for performance. */
    let render {state, updater} =>
      <div>
        <button onClick=(updater dec)> (ReactRe.stringToElement "-") </button>
        <span> (ReactRe.stringToElement (string_of_int state.count)) </span>
        <button onClick=(updater inc)> (ReactRe.stringToElement "+") </button>
      </div>;
  };
  include ReactRe.CreateComponent Component;
  let createElement = wrapProps ();
};

/* What if our stateful component had props as well? */
module DeltaCounter = {
  module Component = {
    include ReactRe.Component.Stateful;
    let name = "Counter";
    type props = {delta: int};
    type state = {count: int};
    let getInitialState _ => {count: 0};
    /* destructure whatever you need out of the componentBag */
    let inc {props, state} _ => Some {count: state.count + props.delta};
    let dec {props, state} _ => Some {count: state.count - props.delta};
    /* just for fun, were going to use the pipe operator |> this time to chain together multiple function applications */
    let render {state, updater} =>
      <div>
        <button onClick=(updater dec)> (ReactRe.stringToElement "-") </button>
        <span> (state.count |> string_of_int |> ReactRe.stringToElement) </span>
        <button onClick=(updater inc)> (ReactRe.stringToElement "+") </button>
      </div>;
  };
  include ReactRe.CreateComponent Component;
  /* make sure you create the labelled arguments down here */
  let createElement ::delta => wrapProps {delta: delta};
};

/* This example shows how the action event is passed to the update handler */
module LoginForm = {
  module Component = {
    include ReactRe.Component.Stateful;
    let name = "LoginForm";
    type props = unit;
    type state = {username: string, password: string};
    let getInitialState _ => {username: "", password: ""};
    /* The event itself is a plain JavaScript object, so you have to use ## instead of . to get the target from the event using BuckleScript syntax. We then use the Reason Document api to get the value from the element. */
    let username {state} event => Some {...state, username: ReasonJs.Document.value event##target};
    let password {state} event => Some {...state, password: ReasonJs.Document.value event##target};
    /* prevent the form from actually being submitted and reset the state */
    let submit _ event => {
      event##preventDefault ();
      Some (getInitialState ())
    };
    /* `type` is a reserved word in Reason so we have to use `_type` instead. */
    let render {state, updater} =>
      <form onSubmit=(updater submit)>
        <input
          _type="text"
          placeholder="username"
          value=state.username
          onChange=(updater username)
        />
        <input
          _type="password"
          placeholder="password"
          value=state.password
          onChange=(updater password)
        />
        <button _type="submit"> (ReactRe.stringToElement "submit") </button>
      </form>;
  };
  include ReactRe.CreateComponent Component;
  let createElement = wrapProps ();
};

/* Lastly, let's look at how we might use an NPM package written i JavaScript. We can require a module from NPM using the [@@bs.module] BuckleScript macro. We can define the the type of the module ourselves, but that takes too long so we can assign a "polymorphic type" and the compiler will infer its type based on how you use it. Glamor is a CSS-in-JS library that we'll use as a demonstration. */
external glamor : 'glamor = "glamor" [@@bs.module];

/* When dealing with plain JavaScript data structures, you have to use ## instead of . and JavaScript objects have quotes around the keys. Here's we're generating a className with the given CSS styles. */
let title: string =
  glamor##css {
    "fontWeight": "bold",
    "fontSize": "32px",
    "color": "rgb(6, 49, 111)",
    "margin": "4px auto 16px auto"
  };

/* We're just going to create a wrapper component here */
module Title = {
  module Component = {
    include ReactRe.Component;
    let name = "Title";
    type props = {children: list ReactRe.reactElement};
    let render {props} =>
      <h1 className=title> (props.children |> Array.of_list |> ReactRe.arrayToElement) </h1>;
  };
  include ReactRe.CreateComponent Component;
  let createElement ::children => wrapProps {children: children} ::children;
};

/* The rest of this tutorial is more of an exploration into building an application with an Elm-like architecture. Proceed at your own risk! I'm basically implementing what's going on in this CodePen: http://codepen.io/ccorcos/pen/jrxbXA?editors=0010 */
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

/* Its a bit annoying that we can't dynamically create a module, but we need to create modules that satisfy the `createElement` type signature, so this is the only way we can get the props in there. */
module type CounterProps = {let decBy: int;};

module ElmishCounter (Props: CounterProps) => {
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

/* Here's the core logic that holds the single-atom state and bootstraps the application. */
module Core (Component: Component) => {
  module CoreClass = {
    include ReactRe.Component.Stateful;
    let name = "Core";
    type props = unit;
    type state = Component.model;
    let getInitialState _ => Component.init;
    let dispatch {state} action => Some (Component.update state action);
    let render {state, updater} => <Component dispatch=(updater dispatch) state />;
  };
  include ReactRe.CreateComponent CoreClass;
  let createElement = wrapProps ();
};

/* Super awkward how you have to specify the props with a module like this... */
module CounterProps = {
  let decBy = 2;
};

/* But here goes nothing! */
module ElmishCounterApp = Core (ElmishCounter CounterProps);

/* Here's another way we can build Core without using another React component. I don't like it as much but it's an interesting demonstration of in-place muttion so I'll leave it here for the reader in case they want to check it out. This way is more aligned with the CodePen implementation. */
module OldCore (Component: Component) => {
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

/* Here's a little combinator that accepts a component and creates two of them. */
module TwoOf (Component: Component) => {
  type model = {one: Component.model, two: Component.model};
  type action =
    | One Component.action
    | Two Component.action;
  type dispatch = action => unit;
  let init = {one: Component.init, two: Component.init};
  let update state action =>
    switch action {
    | One a => {...state, one: Component.update state.one a}
    | Two a => {...state, two: Component.update state.two a}
    };
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

/* Here we're composing with the TwoOf combinator! */
module TwoOfElmishCounterApp = Core (TwoOf (ElmishCounter CounterProps));

/* The List methods aren't all the full featured so we have to make this ourselves. */
let rec firstN n l =>
  switch (n, l) {
  | (0, _) => []
  | (_, []) => []
  | (n, [h, ...t]) => [h, ...firstN (n - 1) t]
  };

/* This combinator makes a component undoable! */
module Undoable (Component: Component) => {
  type model = {time: int, states: list Component.model};
  let init = {time: 0, states: [Component.init]};
  type action =
    | Undo
    | Redo
    | Child Component.action;
  type dispatch = action => unit;
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

module UndoableTwoOfElmishCounterApp = Core (Undoable (TwoOf (ElmishCounter CounterProps)));
