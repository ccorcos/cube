let half = Defs.size /. 2.;

let nhalf = (-1.0) *. half;

/* moves the square so the center is at the origin */
let center = Css.translate3d (nhalf, nhalf, 0.);

/* move the square forward and backward */
let front = Css.translate3d (0., 0., half);

let back = Css.translate3d (0., 0., nhalf);

/* let init = Tensor.id4; */
let init = Tensor.id4 |> Tensor.rotateX (-0.55) |> Tensor.rotateY 0.45;

module Cube = {
  module Component = {
    include ReactRe.Component.Stateful;
    let name = "Cube";
    type props = unit;
    type state = {orientation: Tensor.matrix4, mouse: option Tensor.vector2};
    let getInitialState _ => {orientation: init, mouse: None};
    let spin oldMouse newMouse orientation => {
      let (dx, dy) = Tensor.sub2 newMouse oldMouse;
      orientation |> Tensor.rotateX ((-1.) *. dy) |> Tensor.rotateY dx
    };
    let mouseDown {state} event => {
      let mouse = Cursor.getMouse event;
      Some {...state, mouse: Some mouse}
    };
    let mouseMove {state} event => {
      let mouse = Cursor.getMouse event;
      switch state.mouse {
      | None => None
      | Some p => Some {orientation: spin p mouse state.orientation, mouse: Some mouse}
      }
    };
    let mouseUp {state} event => {
      let mouse = Cursor.getMouse event;
      switch state.mouse {
      | None => None
      | Some p => Some {orientation: spin p mouse state.orientation, mouse: None}
      }
    };
    let render {state, updater} => {
      let rotation = Css.matrix3d state.orientation;
      <div
        className=Styles.wrap
        onMouseDown=(updater mouseDown)
        onTouchStart=(updater mouseDown)
        onMouseMove=(updater mouseMove)
        onTouchMove=(updater mouseMove)
        onMouseUp=(updater mouseUp)
        onTouchEnd=(updater mouseUp)
        onMouseLeave=(updater mouseUp)
        onTouchCancel=(updater mouseUp)>
        <div className=Styles.cube>
          <div
            id="front"
            className=Styles.face
            style={
                    "transform": center ^ " " ^ rotation ^ " " ^ front,
                    "backgroundColor": "#ffffff"
                  }
          />
          <div
            id="back"
            className=Styles.face
            style={"transform": center ^ " " ^ rotation ^ " " ^ back, "backgroundColor": "#000000"}
          />
          <div
            id="left"
            className=Styles.face
            style={
                    "transform": center ^ " " ^ rotation ^ " rotate3d(0, 1, 0, 90deg) " ^ front,
                    "backgroundColor": "#fc9d9d"
                  }
          />
          <div
            id="right"
            className=Styles.face
            style={
                    "transform": center ^ " " ^ rotation ^ " rotate3d(0, 1, 0, 90deg) " ^ back,
                    "backgroundColor": "#ef9efc"
                  }
          />
          <div
            id="bottom"
            className=Styles.face
            style={
                    "transform": center ^ " " ^ rotation ^ " rotate3d(1, 0, 0, 90deg) " ^ front,
                    "backgroundColor": "#f8fc9e"
                  }
          />
          <div
            id="top"
            className=Styles.face
            style={
                    "transform": center ^ " " ^ rotation ^ " rotate3d(1, 0, 0, 90deg) " ^ back,
                    "backgroundColor": "#b6fc9e"
                  }
          />
        </div>
      </div>
    };
  };
  include ReactRe.CreateComponent Component;
  let createElement = wrapProps ();
};
