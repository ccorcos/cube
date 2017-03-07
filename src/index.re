module CounterProps = {
  let decBy = 2;
};

module App1 = Core.Core (Counter.Counter CounterProps);

module App2 = Core.Core (TwoOf.TwoOf (Counter.Counter CounterProps));

let () = App2.start ();
