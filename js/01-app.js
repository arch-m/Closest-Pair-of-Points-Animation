async function loadFile(file) {
  let data = await (new Response(file)).json();
  drawPoints(data);
}

function drawPoints(data) {
  const s = Snap().attr({viewBox: "0 0 1000 1000", padding: "3px"});
  Object.values(data)[0].forEach((point) => {
    let values = point.split(',');
    s.circle(parseInt(values[0])+12, parseInt(values[1])+12, 10).attr({
      fill: "#01BABE",
      stroke: "#D6E8EE",
      strokeWidth: 5
    });
  });

  Object.values(data)[1].forEach((rel) => {
    values_p1 = rel.p_1.split(',');
    values_p2 = rel.p_2.split(',');
    
    s.line(parseInt(values_p1[0])+12,parseInt(values_p1[1])+12,parseInt(values_p2[0])+12,parseInt(values_p2[1])+12).attr({
      fill: "#01BABE",
      stroke: "#97CADB",
      strokeWidth: 3
    });
  });


}

