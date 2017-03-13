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
    let start state point => state |> clearRedo |> pushPoint point;
    let move state point => state |> pushPoint point;
    let stop state point => state |> pushPoint point |> pushPath;
    let undo state => {...state, time: state.time + 1};
    let redo state => {...state, time: state.time - 1};
    let mouseDown {state} event => Some (Cursor.getMouse event |> start state);
    let mouseMove {state} event => Some (Cursor.getMouse event |> move state);
    let mouseUp {state} event => Some (Cursor.getMouse event |> stop state);
    type drawBag = {
      onMouseDown: ReactRe.event => unit,
      onMouseMove: ReactRe.event => unit,
      onMouseUp: ReactRe.event => unit,
      state
    };
    type props = {view: drawBag => ReactRe.reactElement};
    let render {props, state, updater} =>
      props.view {
        onMouseDown: updater mouseDown,
        onMouseMove: updater mouseMove,
        onMouseUp: updater mouseUp,
        state
      };
  };
  include ReactRe.CreateComponent Component;
  let createElement ::view => wrapProps {view: view};
};

module ChooseColor = {
  module Component = {
    include ReactRe.Component;
  };
  /* include ReactRe.CreateComponent Component; */
  /* let createElement ::view => wrapProps {view: view}; */
};
/*
 const ColorPalette = (props) => {
   const colors = colorOptions.map(color =>
     <div
       style={{
         backgroundColor: color,
         height: 24,
         width: 24,
         borderRadius: 24,
         margin: 5,
         borderWidth: 1,
         borderColor: 'black',
         borderStyle: 'solid',
         opacity: props.state.getIn(['style', 'stroke']) === color ? 1 : 0.3,
       }}
       key={color}
       onClick={() => props.onStyle({stroke: color})}
     />
   )
   return (
     <div
       style={{
         display: 'flex',
         alignItems: 'center',
       }}
     >
       <span>Colors:</span>
       {colors}
     </div>
   )
 } */
