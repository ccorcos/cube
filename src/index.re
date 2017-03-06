let state = Counter.init;

let dispatch action => Counter.update ::state ::action;

let root = ReasonJs.Document.getElementById "index";

let () = ReactDOMRe.render <Counter dispatch action decBy=2 /> root;
