/* Getting the div we want to render */
let root = ReasonJs.Document.getElementById "index";

external glamor : 'glamor = "glamor" [@@bs.module];

let () = glamor##css##global "html, body" {"margin": "0", "padding": "0"};

let () = glamor##css##global "*" {"boxSizing": "border-box"};

let section: string =
  glamor##css {"width": "100%", "maxWidth": "30rem", "padding": "16px 8px", "margin": "0 auto"};

let title: string = glamor##css {"fontFamily": "sans-serif"};

module Section = {
  module Component = {
    include ReactRe.Component;
    let name = "Section";
    type props = {title: string, children: list ReactRe.reactElement};
    let render {props} =>
      <article className=section>
        <h1 className=title> (props.title ^ ":" |> ReactRe.stringToElement) </h1>
        <div> (props.children |> Array.of_list |> ReactRe.arrayToElement) </div>
      </article>;
  };
  include ReactRe.CreateComponent Component;
  let createElement ::title ::children => wrapProps {children, title} ::children;
};

let app =
  <div>
    <Section title="Simplest"> <Tutorial.Simplest /> </Section>
    <Section title="SimpleWithProps"> <Tutorial.SimpleWithProps who="chet" /> </Section>
    <Section title="SimpleWrapper">
      <Tutorial.SimpleWrapper>
        (ReactRe.stringToElement "I should be wrapped.")
      </Tutorial.SimpleWrapper>
    </Section>
    <Section title="Counter"> <Tutorial.Counter /> </Section>
    <Section title="DeltaCounter"> <Tutorial.DeltaCounter delta=2 /> </Section>
    <Section title="LoginForm"> <Tutorial.LoginForm /> </Section>
    <Section title="Title">
      <Tutorial.Title> (ReactRe.stringToElement "Hello JS Interop!") </Tutorial.Title>
    </Section>
  </div>;

let () = ReactDOMRe.render app root;
/*
 abstract types (type model) vs generic types (type 'model)
 _ and unit types?

  module CounterProps = {
    let decBy = 2;
  };

  module App1 = Core.Core (Counter.Counter CounterProps);

  module App2 = Core.Core (TwoOf.TwoOf (Counter.Counter CounterProps));

  module App3 = Core.Core (Undoable.Undoable (TwoOf.TwoOf (Counter.Counter CounterProps)));
  /* let () = App3.start (); */ */
