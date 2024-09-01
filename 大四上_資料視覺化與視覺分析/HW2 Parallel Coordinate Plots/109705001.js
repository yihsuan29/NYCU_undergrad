(function (d3$1) {
  'use strict';

  const width = 0.9*window.innerWidth;
  const height = 0.9*window.innerHeight;
  const svg = d3$1.select('svg')
  	.attr('height',height)
    .attr('width',width*0.9);

    

  const features = ['sepal length', 'sepal width', 'petal length', 'petal width'];
  var setosa = '#85a3d4';
  var versicolor = '#d485d4';
  var virginica = '#edda82';

  const color = (d) =>{
    switch(d){
      case 'Iris-setosa': return setosa;
      case 'Iris-versicolor': return versicolor;
      case 'Iris-virginica': return virginica;
    }
  };

  const render = (data) =>{
  	const margin = { top: height*0.20, 
                     right: width*0.15,
                     bottom: height*0.05,
                     left: width*0.15};
  	const innerH = height - margin.top - margin.bottom;
    const innerW = (width - margin.left - margin.right)*0.9;
    
    const g = svg.append('g')
    	.attr('transform',`translate(${margin.left}, ${margin.top})`);

    
    const x = d3$1.scalePoint()
    	.domain(features)
    	.range([0,innerW]);
    
    var y = {};
    var yAxis = {};
    features.forEach(f =>{
    	y[f] = d3$1.scaleLinear()
      	.domain(d3$1.extent(data, d=>d[f]))
      	.range([innerH,0]);
      yAxis[f] = d3$1.axisLeft(y[f])
      	.tickPadding(10);	
    });
    
    const yAxisG = g.selectAll('.domain')
    	.data(features)
    	.enter()
    	.append('g')
    	.each(function(d) {d3$1.select(this).call(yAxis[d]);})
    	.attr('transform',(d) => `translate( ${x(d)},0)`);

    yAxisG.append('text')
    	.text(d =>d)
    	.attr('class','label')
    	.attr('fill','black')
    	.attr('y',-20)
    	.attr('text-anchor','middle');
  	
    var xId = {};
    const xScale = (d) =>
      xId[d] == null ? x(d) : xId[d];

    const path = (d )=>
      d3$1.line()(features.map(p => [xScale(p), y[p](d[p])])); 

    const pathG = g.selectAll('path')
    	.data(data)
    	.enter()
      .append('path')
      .attr('d', path)
      .attr('stroke',  (d) => color(d.class));

    const drag = (d) => {
        xId[d] = Math.min(innerW+30, Math.max(-30, d3.event.x));
        pathG.attr('d', path);
        features.sort((p,q) => xScale(p) - xScale(q));
      	x.domain(features);
      	yAxisG.attr('transform', d => 'translate(' + xScale(d) +',0)');
      }; 
  		
      const transition = g =>  
        g.transition().duration(300);
      		
      
      const dragend = d => {
      	 delete xId[d];
      	 transition(pathG).attr("d", path);
      	 transition(yAxisG).attr("transform", p => "translate(" + x(p) + ",0)");
        
      };

      yAxisG.call(d3.drag()
                .subject({x: x})
                .on('drag', drag)
                .on('end', dragend)
      );  
  };
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
      .append('input')
      .attr("type", "checkbox")
      .attr("checked", true)
      .attr('id', col);
    Lgd
      .append('text')
      .text(col);

  });
  const checkbox_versicolor = document.getElementById('versicolor');
  checkbox_versicolor.addEventListener('change', function() {
    if (checkbox_versicolor.checked) {
      versicolor = '#d485d4';
    } else {
      versicolor = '#e5e2f0'; 
    }
    d3$1.csv('http://vis.lab.djosix.com:2023/data/iris.csv')
    .then(data => {
      const columnNames = Object.keys(data[0]);
      columnNames.pop();
      data.forEach(d => {
        columnNames.forEach(col => {
            d[col] = +d[col];
        });
      });
      data.pop();
      d3.select("svg").selectAll("*").remove();
      render(data);
    });
  });

  const checkbox_virginica = document.getElementById('virginica');
  checkbox_virginica.addEventListener('change', function() {
    if (checkbox_virginica.checked) {
      virginica = '#edda82';
    } else {
      virginica = '#e5e2f0'; 
    }
    d3$1.csv('http://vis.lab.djosix.com:2023/data/iris.csv')
    .then(data => {
      const columnNames = Object.keys(data[0]);
      columnNames.pop();
      data.forEach(d => {
        columnNames.forEach(col => {
            d[col] = +d[col];
        });
      });
      data.pop();
      d3.select("svg").selectAll("*").remove();
      render(data);
    });
  });

  const checkbox_setosa = document.getElementById('setosa');
  checkbox_setosa.addEventListener('change', function() {
    if (checkbox_setosa.checked) {
      setosa = '#85a3d4';
    } else {
      setosa = '#e5e2f0'; 
    }
    d3$1.csv('http://vis.lab.djosix.com:2023/data/iris.csv')
    .then(data => {
      const columnNames = Object.keys(data[0]);
      columnNames.pop();
      data.forEach(d => {
        columnNames.forEach(col => {
            d[col] = +d[col];
        });
      });
      data.pop();
      d3.select("svg").selectAll("*").remove();
      render(data);
    });
  });

  d3$1.csv('http://vis.lab.djosix.com:2023/data/iris.csv')
    .then(data => {
      const columnNames = Object.keys(data[0]);
      columnNames.pop();
      data.forEach(d => {
        columnNames.forEach(col => {
            d[col] = +d[col];
        });
      });
      data.pop();
      render(data);
    });
   


}(d3));