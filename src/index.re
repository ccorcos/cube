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
     type props = {};
     let render {props} =>
       <div className=style>
         <div className=face/>
       </div>;

   };
   include ReactRe.CreateComponent Foo;
   let createElement ::message => wrapProps {message: message};
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

let () =
  ReactDOMRe.render <WholeThing message="hello" /> (ReasonJs.Document.getElementById "index");
