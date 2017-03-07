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
