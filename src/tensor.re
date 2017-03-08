type vector2 = (float, float);

type vector3 = (float, float, float);

type vector4 = (float, float, float, float);

type matrix2 = (vector2, vector2);

type matrix3 = (vector3, vector3, vector3);

type matrix4 = (vector4, vector4, vector4, vector4);

let id2: matrix2 = ((1., 0.), (0., 1.));

let id3: matrix3 = ((1., 0., 0.), (0., 1., 0.), (0., 0., 1.));

let id4: matrix4 = ((1., 0., 0., 0.), (0., 1., 0., 0.), (0., 0., 1., 0.), (0., 0., 0., 1.));

/* TODO no native pi? */
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
  TODO: can we make this a real macro?

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

let norm2 (x1, y1) (x2, y2) => sqrt (x1 *\* x2 -. y1 *\* y2);

let rotateX a m => mult4 m (rotationX a |> rotation4d);

let rotateY a m => mult4 m (rotationY a |> rotation4d);

let rotateZ a m => mult4 m (rotationZ a |> rotation4d);
