let closestDistance = 1001;
let cPointAx, cPointAy, cPointBx, cPointBy;

async function loadFile(file) {
  let data = await (new Response(file)).json();
  drawPoints(data);
}

function drawPoints(data) {
  const s = Snap().attr({viewBox: "0 0 1000 1000", padding: "3px"});
  Object.values(data)[0].forEach((point) => {
    let values = point.split(',');
    s.circle(parseInt(values[0]), parseInt(values[1]), 10).attr({
      fill: "#01BABE",
      stroke: "#D6E8EE",
      strokeWidth: 5
    });
  });

  Object.values(data)[1].forEach((rel, key, arr) => {
    setTimeout(function(){
      values_p1 = rel.p_1.split(',');
      values_p2 = rel.p_2.split(',');

      const x1 = parseInt(values_p1[0]);
      const y1 = parseInt(values_p1[1]);
      const x2 = parseInt(values_p2[0]);
      const y2 = parseInt(values_p2[1]);
      let distance = Math.round(Math.sqrt(Math.pow(x2-x1,2)+Math.pow(y2-y1,2)));   

      const line = s.line(x1,y1,x1,y1).attr({
        fill: "#596666",
        stroke: "#B7BABB",
        strokeWidth: 3
      });

      if (Object.is(arr.length - 1, key)) {
        line.animate({x1: x2, y1: y2}, 1000, mina.easein, () => {
          line.animate({
            fill: "#BE015C",
            stroke: "#DB97A8",
          }, 250, mina.easein, () => {
            line.animate({}, 500, mina.easein, () => {
              line.remove();
              s.line(cPointAx,cPointAy,cPointBx,cPointBy).attr({
                fill: "#01BABE",
                stroke: "#01BABE",
                strokeWidth: 3
              });
            });
          });
        });
      }
      else {
        line.animate({x1: x2, y1: y2}, 1000, mina.easein, () => {
          line.animate({
            fill: "#BE015C",
            stroke: "#DB97A8",
          }, 250, mina.easein, () => {
            setClosestPoints(distance, x1, y1, x2, y2);
            line.animate({}, 500, mina.easein, () => {
              line.remove();
            });
          });
        });
      }
    }, 1750 * key);
  });
}

function setClosestPoints(distance, pointAx, pointAy, pointBx, pointBy) {
  if(distance < closestDistance) {
    closestDistance = distance;
    cPointAx = pointAx;
    cPointAy = pointAy;
    cPointBx = pointBx;
    cPointBy = pointBy;
    document.querySelector('.content p').textContent = distance;
    document.querySelector('.content .points p').textContent = `[(${pointAx},${pointAy}),(${pointBx},${pointBy})],`;
  }
}

function reload() {
  location.reload(); 
}


