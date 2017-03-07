module CounterProps = {
  let decBy = 2;
};

module App = Core.Core (Counter.Counter CounterProps);

let () = App.start ();
