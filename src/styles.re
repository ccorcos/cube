external glamor : 'glamor = "glamor" [@@bs.module];

let css = glamor##css;

let wrap =
  css {
    "cursor": "all-scroll",
    "position": "absolute",
    "top": 0,
    "left": 0,
    "right": 0,
    "bottom": 0
  };

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
