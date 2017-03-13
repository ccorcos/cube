module L = {
  let update (l: list 'a) (index: int) (fn: 'item => 'item) => {
    let f i item => i === index ? fn item : item;
    List.mapi f l
  };
  let rec skip l i =>
    switch (l, i) {
    | (_, 0) => l
    | ([], _) => []
    | ([_, ...t], i) => skip t (i - 1)
    };
};

module Drawing = {
  module Component = {
    include ReactRe.Component.Stateful;
    let name = "Drawing";
    type props = unit;
    type style = {stroke: string, strokeWidth: int};
    type point = Tensor.vector2;
    type path = {style, points: list point};
    type state = {time: int, path, paths: list path};
    let getInitialState _ => {
      time: 0,
      path: {style: {stroke: "black", strokeWidth: 4}, points: []},
      paths: []
    };
    let pushPoint point state => {
      ...state,
      path: {
        ...state.path,
        points:
          switch state.path.points {
          | [] => [point]
          | [h, ...t] =>
            if (Tensor.norm2 point h < Defs.minDelta) {
              [h, ...t]
            } else {
              [point, h, ...t]
            }
          }
      }
    };
    let clearRedo state => {...state, time: 0, paths: L.skip state.paths state.time};
    let changeStroke stroke state => {
      ...state,
      path: {...state.path, style: {...state.path.style, stroke}}
    };
    let changeStrokeWidth strokeWidth state => {
      ...state,
      path: {...state.path, style: {...state.path.style, strokeWidth}}
    };
    let pushPath state => {
      ...state,
      path: {...state.path, points: []},
      paths: [state.path, ...state.paths]
    };
    let start point state => state |> clearRedo |> pushPoint point;
    let move point state => state |> pushPoint point;
    let stop point state => state |> pushPoint point |> pushPath;
    let undo state => {...state, time: state.time + 1};
    let redo state => {...state, time: state.time - 1};
    /* HERE */
    let render _ => <svg className=Styles.drawing />;
  };
  include ReactRe.CreateComponent Component;
  let createElement = wrapProps ();
};
