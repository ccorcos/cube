type store = {mutable state: Counter.model};

let store = {state: Counter.init};

let root = ReasonJs.Document.getElementById "index";

let rec dispatch action => {
  store.state = Counter.update store.state action;
  render store.state
}
and render state => ReactDOMRe.render <Counter dispatch state decBy=2 /> root;

render store.state;
