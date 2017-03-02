/*
 external glamor : _ = "glamor" [@@bs.module];

 let style = glamor##css({
   color: "red",
 })
 */
module WholeThing = {
  module Foo = {
    include ReactRe.Component;
    let name = "Foo";
    type props = {message: string};
    let render {props} =>
      <div style={"color": "red"}> (ReactRe.stringToElement props.message) </div>;
  };
  include ReactRe.CreateComponent Foo;
  let createElement ::message => wrapProps {message: message};
};

let () =
  ReactDOMRe.render <WholeThing message="hello" /> (ReasonJs.Document.getElementById "index");
