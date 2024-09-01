(function () {
  'use strict';

  const width = window.innerWidth;
  const height = window.innerHeight;
  const marginOut = {left:120, right:30, top:10, bottom:50};
  const sizeOut = height- marginOut.top - marginOut.bottom;

  const svg = d3.select('svg')
  	.attr('height',sizeOut+ marginOut.top + marginOut.bottom)
    .attr('width',sizeOut+ marginOut.left + marginOut.right)
  	.append('g')
    	.attr('transform',`translate(${marginOut.left}, ${marginOut.top})`);

  let selectedData = [];
  const render = (data) =>{
  	var features = ['sepal length', 'sepal width', 'petal length', 'petal width'];
  	var numFt = features.length;
    
    var marginIn =10;
    var sizeIn = sizeOut/numFt;
    
    var plotPos = d3.scalePoint()
    	.domain(features)
    	.range([0,sizeOut-sizeIn]);
    
    var setosa = '#85a3d4';
    var versicolor = '#d485d4';
    var virginica = '#edda82';
    
    const color = (d) =>{
      switch(d){
        case 'Iris-setosa': return setosa;
        case 'Iris-versicolor': return versicolor;
        case 'Iris-virginica': return virginica;
      }  };
    
    svg.selectAll(".x-axis-label")
      .data(features)
      .enter()
      .append("text")
        .attr("class", "x-axis-label")
        .attr("x", (d) => plotPos(d) + sizeIn / 2)
        .attr("y", sizeOut + marginOut.top + 20) 
        .text((d) => d)
        .style("text-anchor", "middle")
      	.style("font-size", "0.8em") 
    		.style("fill", "#8e8883");
    
    svg.selectAll(".y-axis-label")
      .data(features)
      .enter()
      .append("text")
        .attr("class", "y-axis-label")
        .attr("x", -20)
        .attr("y", (d) => plotPos(d) + sizeIn / 2)
        .text((d) => d)
        .style("text-anchor", "end")
        .attr("alignment-baseline", "middle")    	
      	.style("font-size", "0.8em") 
    		.style("fill", "#8e8883");

    for (var i in features) {
      for (var j in features) {

          var f1 = features[i];
          var f2 = features[j];

          var x = d3.scaleLinear()
              .domain( d3.extent(data, (d)=>d[f1]))
          		.nice()
              .range([ 0, sizeIn - 2*marginIn ]);
          var y = d3.scaleLinear()
              .domain(d3.extent(data, (d)=>d[f2]))
              .nice()
              .range([ sizeIn - 2*marginIn, 0 ]);
        
          if (f1 === f2) {
            var tmp1 = svg
            .append('g')
            .attr("transform",`translate(${(plotPos(f1)+marginIn)},${(plotPos(f2)+marginIn)})`);


            tmp1.append("g")
                .attr("transform",`translate(0,${sizeIn-marginIn*2})`)
                .call(d3.axisBottom(x).ticks(5));

            var numBins = 10;
  			
            var hist = d3.histogram()
                .value((d)=>d[f1])
                .domain(x.domain())
            		.thresholds(d3.range(x.domain()[0],x.domain()[1],(x.domain()[1]-x.domain()[0])/numBins));
  					
            var data1 = data.filter(item => selectedData.includes(item) && item['class'] === 'Iris-setosa');
            var data2 = data.filter(item => selectedData.includes(item) && (item['class'] === 'Iris-setosa'||item['class'] === 'Iris-versicolor'));
            var data3 = data.filter(item => selectedData.includes(item));
            
            var bins = hist(data);
            var bins1 = hist(data1);
            var bins2 = hist(data2);          
            var bins3 = hist(data3);
            
            var yCount = d3.scaleLinear()
              .domain([0, d3.max(bins, (d) => d.length)])
              .range([sizeIn - 2 * marginIn, 0]);

            tmp1.append("g")
              .call(d3.axisLeft(yCount).ticks(5));
  	

            y = d3.scaleLinear()
                .range([ sizeIn - 2*marginIn, 0 ])
                .domain([0, d3.max(bins, (d)=>d.length)]);

            tmp1.append('g')
                .selectAll("rect")
                .data(bins)
                .enter()
                .append("rect")
                  .attr("x", 1)
                  .attr("transform", (d)=>`translate(${x(d.x0)},${y(d.length)})`)
                  .attr("width", (d)=> x(d.x1) - x(d.x0))
                  .attr("height", (d)=> (sizeIn -2*marginIn) - y(d.length))
                  .style("fill", "#c0c0bb")
                  .attr("stroke", "white");
            
            tmp1.append('g')
                .selectAll("rect")
                .data(bins3)
                .enter()
                .append("rect")
                  .attr("x", 1)
                  .attr("transform", (d)=>`translate(${x(d.x0)},${y(d.length)})`)
                  .attr("width", (d)=> x(d.x1) - x(d.x0))
                  .attr("height", (d)=> (sizeIn -2*marginIn) - y(d.length))
                  .style("fill", virginica)
                  .attr("stroke", "white");
            
            tmp1.append('g')
                .selectAll("rect")
                .data(bins2)
                .enter()
                .append("rect")
                  .attr("x", 1)
                  .attr("transform", (d)=>`translate(${x(d.x0)},${y(d.length)})`)
                  .attr("width", (d)=> x(d.x1) - x(d.x0))
                  .attr("height", (d)=> (sizeIn -2*marginIn) - y(d.length))
                  .style("fill",  versicolor)
                  .attr("stroke", "white");
            
            tmp1.append('g')
                .selectAll("rect")
                .data(bins1)
                .enter()
                .append("rect")
                  .attr("x", 1)
                  .attr("transform", (d)=>`translate(${x(d.x0)},${y(d.length)})`)
                  .attr("width", (d)=> x(d.x1) - x(d.x0))
                  .attr("height", (d)=> (sizeIn -2*marginIn) - y(d.length))
                  .style("fill", setosa)
                  .attr("stroke", "white");
          }
          else {
            const brush = d3.brush()
                  .extent([[0, 0], [sizeIn - 2 * marginIn, sizeIn - 2 * marginIn]])
                  .on("end", brushed(f1,f2,data,sizeIn,marginIn));

            const tmp2 = svg
              .append('g')
              .attr("transform",`translate(${(plotPos(f1)+marginIn)},${(plotPos(f2)+marginIn)})`);


            tmp2.append("g")
                .attr("transform",`translate(0,${sizeIn-marginIn*2})`)
                .call(d3.axisBottom(x).ticks(3));

            tmp2.append("g")
              .call(d3.axisLeft(y).ticks(3));

            tmp2.append("g")
                .attr("class", "brush")
                .call(brush);


            const circle = tmp2.selectAll("circle")
                .data(data)
                .enter()
                .append("circle")
                  .attr("cx", (d) => x(d[f1]))
                  .attr("cy", (d) => y(d[f2]))
                  .attr("r", 2)
                  .attr("fill", (d) => {
                      return selectedData.includes(d) ? color(d.class) : "#c0c0bb";
                  });       			
  				}      
  			}	
    	}  
  };
  d3.csv('http://vis.lab.djosix.com:2023/data/iris.csv')
    .then(data => {
      const columnNames = Object.keys(data[0]);
      columnNames.pop();
      data.forEach(d => {
        columnNames.forEach(col => {
            d[col] = +d[col];
        });
      });
      data.pop();
    	selectedData = data;
    	render(data);
    
    	
    });

  function brushed(f1, f2,data,sizeIn,marginIn) {
    return function() {
        var x = d3.scaleLinear()
            .domain( d3.extent(data, (d)=>d[f1]))
            .nice()
            .range([ 0, sizeIn - 2*marginIn ]);
        var y = d3.scaleLinear()
            .domain(d3.extent(data, (d)=>d[f2]))
            .nice()
            .range([ sizeIn - 2*marginIn, 0 ]);
        const selection = d3.event.selection;
        console.log(selection);
        if (selection) {
            selectedData = data.filter(d => {
                const xVal = x(d[f1]);
                const yVal = y(d[f2]);     
                return xVal >= selection[0][0] && xVal <= selection[1][0] &&
                    yVal >= selection[0][1] && yVal <= selection[1][1];
            });
        }
      svg.selectAll('*').remove();
      render(data);
    };
  }

  const Class=['setosa','versicolor','virginica'];

  const legend= d3.select('#LegendMenu')
      .attr('width', 0.1* width)
      .attr('height', height);
  const legends = legend.append('legends');
  legends.attr('class','item');
  legends.append('text').text('Class');

  Class.forEach(col => {
    legends.append('br');
    const Lgd = legends
      .append('span');
    Lgd
      .append('dot')
      .attr('class','dot')
      .attr('id', col);
    Lgd
      .append('text')
      .text(col);

  });

}());