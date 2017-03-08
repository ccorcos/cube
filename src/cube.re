external glamor : 'glamor = "glamor" [@@bs.module];

let css = glamor##css;

module Defs = {
  let size = 200.;
  let half = size /. 2.;
  let nhalf = (-1.0) *. half;
};

module Styles = {
  /* let wrap = ""; */
  let wrap = css {"position": "absolute", "top": 0, "left": 0, "right": 0, "bottom": 0};
  let cube =
    css {
      "position": "absolute",
      "top": "50%",
      "left": "50%",
      "perspective": "500px",
      "transformStyle": "preserve-3d"
    };
  let face =
    css {
      "borderStyle": "solid",
      "borderWidth": 1,
      "borderColor": "black",
      "height": Defs.size,
      "width": Defs.size,
      "position": "absolute"
    };
};

/* TODO infix operators for add subtract multiply */
module Tensor = {
  type vector2 = (float, float);
  type vector3 = (float, float, float);
  type vector4 = (float, float, float, float);
  type matrix2 = (vector2, vector2);
  let id2: matrix2 = ((1., 0.), (0., 1.));
  type matrix3 = (vector3, vector3, vector3);
  let id3: matrix3 = ((1., 0., 0.), (0., 1., 0.), (0., 0., 1.));
  type matrix4 = (vector4, vector4, vector4, vector4);
  let id4: matrix4 = ((1., 0., 0., 0.), (0., 1., 0., 0.), (0., 0., 1., 0.), (0., 0., 0., 1.));
  let pi = 2. *. acos 0.;
  let degrees_of_radians rad => rad *. 180. /. pi;
  let radians_of_degrees deg => deg *. pi /. 180.;
  /* Euclidian 3-space rotations */
  let rotationX a => ((1., 0., 0.), (0., cos a, sin a), (0., (-1.) *. sin a, cos a));
  let rotationY a => ((cos a, 0., (-1.) *. sin a), (0., 1., 0.), (sin a, 0., cos a));
  let rotationZ a => ((cos a, sin a, 0.), ((-1.) *. sin a, cos a, 0.), (0., 0., 1.));
  /* turn a 3d rotaion into a 3d rotation */
  let rotation4d ((a, b, c), (d, e, f), (g, h, i)) => (
    (a, b, c, 0.),
    (d, e, f, 0.),
    (g, h, i, 0.),
    (0., 0., 0., 1.)
  );
  /*
    Generated with the following python code:

    a = lambda x, y: 'a' + str(x) + str(y)
    b = lambda x, y: 'b' + str(x) + str(y)
    c = [[' +. '.join([a(z,y) + ' *. ' + b(y,x) for y in range(1, 5)]) for x in range(1, 5)]  for z in range(1, 5)]
    t = lambda l: '(' + ', '.join(l) +  ')'
    d = t([t(x) for x in c])

   */
  let mult4
      ((a11, a12, a13, a14), (a21, a22, a23, a24), (a31, a32, a33, a34), (a41, a42, a43, a44))
      ((b11, b12, b13, b14), (b21, b22, b23, b24), (b31, b32, b33, b34), (b41, b42, b43, b44)) => (
    (
      a11 *. b11 +. a12 *. b21 +. a13 *. b31 +. a14 *. b41,
      a11 *. b12 +. a12 *. b22 +. a13 *. b32 +. a14 *. b42,
      a11 *. b13 +. a12 *. b23 +. a13 *. b33 +. a14 *. b43,
      a11 *. b14 +. a12 *. b24 +. a13 *. b34 +. a14 *. b44
    ),
    (
      a21 *. b11 +. a22 *. b21 +. a23 *. b31 +. a24 *. b41,
      a21 *. b12 +. a22 *. b22 +. a23 *. b32 +. a24 *. b42,
      a21 *. b13 +. a22 *. b23 +. a23 *. b33 +. a24 *. b43,
      a21 *. b14 +. a22 *. b24 +. a23 *. b34 +. a24 *. b44
    ),
    (
      a31 *. b11 +. a32 *. b21 +. a33 *. b31 +. a34 *. b41,
      a31 *. b12 +. a32 *. b22 +. a33 *. b32 +. a34 *. b42,
      a31 *. b13 +. a32 *. b23 +. a33 *. b33 +. a34 *. b43,
      a31 *. b14 +. a32 *. b24 +. a33 *. b34 +. a34 *. b44
    ),
    (
      a41 *. b11 +. a42 *. b21 +. a43 *. b31 +. a44 *. b41,
      a41 *. b12 +. a42 *. b22 +. a43 *. b32 +. a44 *. b42,
      a41 *. b13 +. a42 *. b23 +. a43 *. b33 +. a44 *. b43,
      a41 *. b14 +. a42 *. b24 +. a43 *. b34 +. a44 *. b44
    )
  );
  let sub2 (x1, y1) (x2, y2) => (x1 -. x2, y1 -. y2);
};

module Css = {
  /* TODO ugly way of formatting floats to work with CSS */
  let fmtfloat n => string_of_float n ^ "0";
  let translate3d (x, y, z) =>
    "translate3d(" ^ fmtfloat x ^ "px, " ^ fmtfloat y ^ "px, " ^ fmtfloat z ^ "px)";
  /* ironically wants a 4d matrix */
  let matrix3d ((a, b, c, d), (e, f, g, h), (i, j, k, l), (m, n, o, p)) => {
    let fmt n => fmtfloat n ^ ", ";
    "matrix3d(" ^
    fmt a ^
    fmt b ^
    fmt c ^
    fmt d ^
    fmt e ^
    fmt f ^
    fmt g ^ fmt h ^ fmt i ^ fmt j ^ fmt k ^ fmt l ^ fmt m ^ fmt n ^ fmt o ^ fmtfloat p ^ ")"
  };
};

/* moves the square so the center is at the origin */
let center = Css.translate3d (Defs.nhalf, Defs.nhalf, 0.);

/* move the square forward and backward */
let front = Css.translate3d (0., 0., Defs.half);

let back = Css.translate3d (0., 0., Defs.nhalf);

/* TODO this should belong in Reason */
external getBoundingClientRect : ReasonJs.Document.element => 'fuckit =
  "getBoundingClientRect" [@@bs.send];

/* TODO added the following to reactRe. Shold be an int and would require some conversion. how to go from int to float??
   pageX : float,
   pageY : float, */
let getMouse event => {
  let rect = getBoundingClientRect event##currentTarget;
  ((event##pageX -. rect##left) /. Defs.size, (event##pageY -. rect##top) /. Defs.size)
};

/* What if our stateful component had props as well? */
module Cube = {
  module Component = {
    include ReactRe.Component.Stateful;
    let name = "Cube";
    type props = unit;
    type state = {orientation: Tensor.matrix4, mouse: option Tensor.vector2};
    let getInitialState _ => {orientation: Tensor.id4, mouse: None};
    let spin oldMouse newMouse orientation => {
      let (dx, dy) = Tensor.sub2 newMouse oldMouse;
      let spinX = Tensor.rotationX ((-1.) *. dy) |> Tensor.rotation4d;
      let spinY = Tensor.rotationY dx |> Tensor.rotation4d;
      Tensor.mult4 (Tensor.mult4 orientation spinY) spinX
    };
    let mouseDown {state} event => {
      let mouse = getMouse event;
      Some {...state, mouse: Some mouse}
    };
    let mouseMove {state} event => {
      let mouse = getMouse event;
      switch state.mouse {
      | None => None
      | Some p => Some {orientation: spin p mouse state.orientation, mouse: Some mouse}
      }
    };
    let mouseUp {state} event => {
      let mouse = getMouse event;
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
