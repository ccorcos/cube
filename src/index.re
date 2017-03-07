/* Getting the div we want to render */
let root = ReasonJs.Document.getElementById "index";

module Section = {
  module Component = {
    include ReactRe.Component;
    let name = "Section";
    type props = {children: list ReactRe.reactElement};
    let render {props} => <div> (ReactRe.arrayToElement (Array.of_list props.children)) </div>;
  };
  include ReactRe.CreateComponent Component;
  let createElement ::children => wrapProps {children: children} ::children;
};

let app =
  <div>
    <div> <strong> (ReactRe.stringToElement "Simplest:") </strong> <Tutorial.Simplest /> </div>
    <div>
      <strong> (ReactRe.stringToElement "SimpleWithProps:") </strong>
      <Tutorial.SimpleWithProps who="chet" />
    </div>
    <div>
      <strong> (ReactRe.stringToElement "SimpleWrapper:") </strong>
      <Tutorial.SimpleWrapper>
        (ReactRe.stringToElement "I should be wrapped.")
      </Tutorial.SimpleWrapper>
    </div>
    <div> <strong> (ReactRe.stringToElement "Counter:") </strong> <Tutorial.Counter /> </div>
    <div>
      <strong> (ReactRe.stringToElement "DeltaCounter:") </strong>
      <Tutorial.DeltaCounter delta=2 />
    </div>
    <div> <strong> (ReactRe.stringToElement "LoginForm:") </strong> <Tutorial.LoginForm /> </div>
  </div>;

let () = ReactDOMRe.render app root;
/*

 More Demos:
 - js interop with glamor

  */
/*
 module CounterProps = {
   let decBy = 2;
 };

 module App1 = Core.Core (Counter.Counter CounterProps);

 module App2 = Core.Core (TwoOf.TwoOf (Counter.Counter CounterProps));

 module App3 = Core.Core (Undoable.Undoable (TwoOf.TwoOf (Counter.Counter CounterProps)));
 /* let () = App3.start (); */ */
