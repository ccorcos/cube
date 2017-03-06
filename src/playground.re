/* This is meant to be a simple stateless counter with a Redux-/Elm-/PureScript-like architecture. */
module Counter = {
  include ReactRe.Component;
};

external glamor : 'glamor = "glamor" [@@bs.module];

let style: string = glamor##css {"color": "blue"};

let size = 200;

let face: string =
  glamor##css {
    "borderStyle": "solid",
    "borderWidth": 1,
    "borderColor": "black",
    "height": size,
    "width": size,
    "position": "absolute"
  };

module Cube = {
  module Cube2 = {
    include ReactRe.Component;
    let name = "Cube";
    type props = unit;
    let render _ => <div className=style> <div className=face /> </div>;
  };
  include ReactRe.CreateComponent Cube2;
  let createElement = wrapProps ();
};

module WholeThing = {
  module Foo = {
    include ReactRe.Component;
    let name = "Foo";
    type props = {message: string};
    let render {props} => <div className=style> (ReactRe.stringToElement props.message) </div>;
  };
  include ReactRe.CreateComponent Foo;
  let createElement ::message => wrapProps {message: message};
};
