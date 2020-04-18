let init: string => unit = [%bs.raw
  {|
function (id) {
  var canvas = document.getElementById(id);
  var clientRect = canvas.getBoundingClientRect();
  var context = canvas.getContext("2d");
  var lineWidth = 0;
  var isMousedown = false;
  var points = [];

  canvas.width = clientRect.width * 2;
  canvas.height = clientRect.height * 2;

  var baseLineWidth = 20;

  ["touchstart", "mousedown"].forEach(function (ev) {
    canvas.addEventListener(ev, function (e) {
      console.log("mousedown");
      var pressure = 0.1;
      var x, y;
      if (
        e.touches &&
        e.touches[0] &&
        typeof e.touches[0]["force"] !== "undefined"
      ) {
        if (e.touches[0]["force"] > 0) {
          pressure = e.touches[0]["force"];
        }
        x = e.touches[0].pageX * 2;
        y = e.touches[0].pageY * 2;
      } else {
        pressure = 1.0;
        x = e.pageX * 2;
        y = e.pageY * 2;
      }

      x -= 2 * clientRect.left;
      y -= 2 * clientRect.top;

      console.log("x, y", x, y);

      isMousedown = true;

      lineWidth = Math.log(pressure + 1) * baseLineWidth;
      context.lineWidth = lineWidth; // pressure * 50;
      context.strokeStyle = "black";
      context.lineCap = "round";
      context.lineJoin = "round";
      context.beginPath();
      context.moveTo(x, y);

      points.push({ x, y, lineWidth });
    });
  });
  ["touchmove", "mousemove"].forEach(function (ev) {
    canvas.addEventListener(ev, function (e) {
      console.log("mousemove");
      if (!isMousedown) return;
      e.preventDefault();

      var pressure = 0.1;
      var x, y;
      if (
        e.touches &&
        e.touches[0] &&
        typeof e.touches[0]["force"] !== "undefined"
      ) {
        if (e.touches[0]["force"] > 0) {
          pressure = e.touches[0]["force"];
        }
        x = e.touches[0].pageX * 2;
        y = e.touches[0].pageY * 2;
      } else {
        pressure = 1.0;
        x = e.pageX * 2;
        y = e.pageY * 2;
      }

      x -= 2 * clientRect.left;
      y -= 2 * clientRect.top;

      // smoothen line width
      lineWidth = Math.log(pressure + 1) * baseLineWidth * 0.2 + lineWidth * 0.8;
      points.push({ x, y, lineWidth });

      context.strokeStyle = "black";
      context.lineCap = "round";
      context.lineJoin = "round";

      if (points.length >= 3) {
        var l = points.length - 1;
        var xc = (points[l].x + points[l - 1].x) / 2;
        var yc = (points[l].y + points[l - 1].y) / 2;

        // xc -= 2 * clientRect.left;
        // yc -= 2 * clientRect.top;

        context.lineWidth = points[l - 1].lineWidth;
        context.quadraticCurveTo(points[l - 1].x, points[l - 1].y, xc, yc);
        context.stroke();
        context.beginPath();
        context.moveTo(xc, yc);
      }
    });
  });
  ["touchend", "touchleave", "mouseup"].forEach(function (ev) {
    canvas.addEventListener(ev, function (e) {
      console.log("mouseup");
      var pressure = 0.1;
      var x, y;

      if (
        e.touches &&
        e.touches[0] &&
        typeof e.touches[0]["force"] !== "undefined"
      ) {
        if (e.touches[0]["force"] > 0) {
          pressure = e.touches[0]["force"];
        }
        x = e.touches[0].pageX * 2;
        y = e.touches[0].pageY * 2;
      } else {
        pressure = 1.0;
        x = e.pageX * 2;
        y = e.pageY * 2;
      }

      x -= 2 * clientRect.left;
      y -= 2 * clientRect.top;

      isMousedown = false;

      context.strokeStyle = "black";
      context.lineCap = "round";
      context.lineJoin = "round";

      if (points.length >= 3) {
        var l = points.length - 1;
        context.quadraticCurveTo(points[l].x, points[l].y, x, y);
        context.stroke();
      }

      points = [];
      lineWidth = 0;
    });
  });
}
|}
];

[@react.component]
let make = (~id) => {
  let width: string = [%bs.raw {|window.innerWidth|}];
  let height: string = [%bs.raw {|window.innerHeight|}];
  React.useEffect(() => {
    init(id);
    None;
  });
  <canvas id width height />;
};