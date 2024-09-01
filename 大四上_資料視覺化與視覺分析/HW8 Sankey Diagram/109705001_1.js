const columnNames = ['buy','maint','door','person','lug','safety','class'];
var x_key = ['buy','maint','door','person','lug','safety','class'];

var units = "Widgets";

// format variables
var formatNumber = d3.format(",.0f"),    // zero decimal places
    format = function(d) { return formatNumber(d) + " " + units; }

const color_keys = [
  'buy_vhigh','buy_high','buy_med','buy_low',
  'maint_vhigh','maint_high','maint_med','maint_low',
  'door_2','door_3','door_4','door_5more',
  'person_2','person_4','person_more',
  'lug_small','lug_med','lug_big',
  'safety_low','safety_med','safety_high',
  'class_unacc','class_acc','class_good','class_vgood'
];

const color_picks = [
  "#9f1e20","#d13e41","#eb7c7e","#f2abac",
  "#28701e","#478f3e","#6fb766","#aadca3",
  "#ffbd7b","#f79e45","#cc7a27","#a75502",
  "#b1dbd7","#62ada6","#2c857d",
  "#f9e59c","#edc949","#cea81d",
  "#d7b3ce","#9f6891","#7b406c",
  "#9fbedf","#6a97c7","#3e6896","#1a3c61"
];

var color = d3
  .scaleOrdinal()
  .domain(color_keys)
  .range(color_picks);

var rect_color_pick = ["#f2abac", "#aadca3", "#ffbd7b", "#b1dbd7","#f9e59c", "#d7b3ce","#9fbedf"];
var rect_color_key = ['buy','maint','door','person','lug','safety','class'];
var rect_color = d3
  .scaleOrdinal()
  .domain(rect_color_key)
  .range(rect_color_pick);

var textMenu = d3.select("#TextMenu");
var textMenuHeight = textMenu.node().getBoundingClientRect().height;

// set the dimensions and margins of the graph
var margin = {top: 0, right: 10, bottom: 10, left: 10},
    width = window.innerWidth - margin.left - margin.right,
    height = window.innerHeight - margin.top - margin.bottom -textMenuHeight -50;

var LgdMenu = d3.select("#LgdMenu").append("svg")
    .attr("width", width + margin.left + margin.right)
    .attr("height", 40)
var svg = d3.select("#svg").append("svg")
    .attr("width", width + margin.left + margin.right)
    .attr("height", height + margin.top + margin.bottom)
  .append("g")
    .attr("transform", 
          "translate(" + margin.left + "," + margin.top + ")");

var tooltip = d3.select("body").append("div")
  .attr("class", "tooltip")
  .style("opacity", 0);

function showTooltip(d, source, target, count) {
  tooltip.html(`
    <text>${source} => ${target}</text><br>
    <text>Count: ${count}</text> <br>
  `);
  tooltip.style("opacity", 1);
}

// Set the sankey diagram properties
var sankey = d3.sankey()
    .nodeWidth(10)
    .nodePadding(40)
    .size([width, height]);

var path = sankey.link();

const render = (drawdata,x_key)=>{
    //算了各種組合後 選這些出來畫
  data = [];
  for (var i = 0; i < x_key.length - 1; i++) {
    data = data.concat(drawdata[x_key[i]][x_key[i+1]])
	}
  //set up graph in same style as original example but empty
  graph = {"nodes" : [], "links" : []};

  data.forEach(function (d) {
    graph.nodes.push({ "name": d.source });
    graph.nodes.push({ "name": d.target });
    graph.links.push({ "source": d.source,
                       "target": d.target,
                       "value": +d.value });
   });

  // return only the distinct / unique nodes
  graph.nodes = d3.keys(d3.nest()
    .key(function (d) { return d.name; })
    .object(graph.nodes));

  // loop through each link replacing the text with its index from node
  graph.links.forEach(function (d, i) {
    graph.links[i].source = graph.nodes.indexOf(graph.links[i].source);
    graph.links[i].target = graph.nodes.indexOf(graph.links[i].target);
  });

  // now loop through each nodes to make nodes an array of objects
  // rather than an array of strings
  graph.nodes.forEach(function (d, i) {
    graph.nodes[i] = { "name": d };
  });
  
  sankey
      .nodes(graph.nodes)
      .links(graph.links)
      .layout(32);

  // add in the links
  var link = svg.append("g").selectAll(".link")
      .data(graph.links)
    	.enter().append("path")
      .attr("class", "link")
      .attr("d", path)
      .style("stroke-width", function(d) { return Math.max(1, d.dy); })
      .sort(function(a, b) { return b.dy - a.dy; });

  // add the link titles
  // link.append("title")
  //       .text(function(d) {
  //   		return d.source.name + " → " + 
  //               d.target.name + "\n" + format(d.value); });
  link
  .on("mouseover", function(d) {
    			showTooltip(d,d.source.name,d.target.name,d.value);
  })
  .on("mousemove", function(d) {
    const tooltipWidth = tooltip.node().offsetWidth;
    const tooltipX = d3.event.pageX + 10;
    const maxX = window.innerWidth - tooltipWidth - 20;
    tooltip
      .style("left", d3.min([d3.event.pageX + 10, maxX]) + "px")
			.style("top", (d3.event.pageY - 30) + "px");
  })
  .on("mouseout", function(d) {
    tooltip.style("opacity", 0);
  });
    

  // add in the nodes
  var node = svg.append("g").selectAll(".node")
      .data(graph.nodes)
    .enter().append("g")
      .attr("class", "node")
      .attr("transform", function(d) { 
		  return "translate(" + d.x + "," + d.y + ")"; })
      .call(d3.drag()
        .subject(function(d) {
          return d;
        })
        .on("start", function() {
          this.parentNode.appendChild(this);
        })
        .on("drag", dragmove));

  // add the rectangles for the nodes
  node.append("rect")
      .attr("height", function(d) { return d.dy; })
      .attr("width", sankey.nodeWidth())
      .style("fill", function(d) { 
		  return d.color = color(d.name.replace(/ .*/, "")); })
      .style("stroke", function(d) { 
		  return d3.rgb(d.color).darker(2); })
    	.append("title")
      .text(function(d) { 
		  return d.name + "\n" + format(d.value); });

  // add in the title for the nodes
  node.append("text")
      .attr("x", -3)
      .attr("y", function(d) { return d.dy / 2; })
      .attr("dy", ".35em")
      .attr("text-anchor", "end")
      .attr("transform", null)
      .text(function(d) {
          return d.name.split("_")[1];
      })
    	.filter(function(d) { return d.x < width / 2; })
      .attr("x", 3 + sankey.nodeWidth())
      .attr("text-anchor", "start");

  //the function for moving the nodes
  function dragmove(d) {
    d3.select(this)
      .attr("transform", 
            "translate(" 
               + d.x + "," 
               + (d.y = Math.max(
                  0, Math.min(height - d.dy, d3.event.y))
                 ) + ")");
    sankey.relayout();
    link.attr("d", path);
  }



  //Lgd============================================================================
  const Lgdx = d3.scalePoint()
  	.domain(x_key)
  	.range([35,width-15]);
   
  const LgdG =LgdMenu.selectAll('.domain')
  	.data(x_key)
  	.enter()
  	.append('g')
  	.attr('transform', (d) => `translate(${Lgdx(d)}, 25)`);

  LgdG
  .append('rect') 
  .attr('width', 50)
  .attr('height', 20)
  .attr('x', -25) 
  .attr('y', -15)  
  .attr('fill', (d) => rect_color(d));
  LgdG
    .append('text')
    .text(d => d)
    .attr('x', 0)
    .attr('y', 0) // Center the text vertically
    .attr('class', 'label')
    .attr('fill', 'black')
    .style('text-anchor', 'middle');
	
  var LgdxId = {};
  const LgdxScale = (d) =>
    LgdxId[d] == null ? Lgdx(d) : LgdxId[d];


  const drag = (d) => {
      LgdxId[d] = Math.min(width+30, Math.max(-30, d3.event.x));
      x_key.sort((p,q) => LgdxScale(p) - LgdxScale(q));
    	Lgdx.domain(x_key);
    	LgdG.attr('transform', d => 'translate(' + LgdxScale(d) +', 25)');
    }; 
		
    const transition = g =>  
      g.transition().duration(300);
    		
    
    const dragend = d => {
    	 delete LgdxId[d];
    	 transition(LgdG).attr("transform", p => "translate(" + Lgdx(p) + ",25)");
      svg.selectAll('*').remove();
       LgdMenu.selectAll('*').remove();
      render(drawdata, x_key);
      
      
    };

    LgdG.call(d3.drag()
              .subject({x: Lgdx})
              .on('drag', drag)
              .on('end', dragend)
    );  
};

// load the data
d3.text('http://vis.lab.djosix.com:2023/data/car.data').then((data) => {
  //讀檔變表
  var rows = data.trim().split('\n');
  var result = [];
  rows.forEach(function(r) {
    var values = r.split(',');
    var obj = {};
    columnNames.forEach((key, index)=>{
        obj[key] = values[index];
    });
    result.push(obj);
	});
  data = result;
  //建一個要畫畫的表
  var drawdata = [];
  columnNames.forEach(function(i){
    var innerArray = [];
    columnNames.forEach(function(j){
      innerArray[j] = [];
    });
    drawdata[i] = innerArray;
  });  
  //原本的資料變source, target, value
  data.forEach(function(d){
    columnNames.forEach(function(i){      
      columnNames.forEach(function(j){ 
        var i_value = i+"_"+d[i];
        var j_value = j+"_"+d[j];
        var existingData = drawdata[i][j].find(function(d_) {
            return d_.source === i_value && d_.target === j_value;
        });
        if (existingData) {
            existingData.value += 1;
        } else {
            drawdata[i][j].push({source:i_value,target:j_value,value:1});
        } 
        
      });
    });
  });

  render(drawdata,x_key);
});
