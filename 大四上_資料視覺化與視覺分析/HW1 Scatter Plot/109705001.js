(function (d3) {
  'use strict';

  const loadData = () =>
    d3.csv('http://vis.lab.djosix.com:2023/data/iris.csv').then(data => {
    const columnNames = Object.keys(data[0]);
    columnNames.pop();
    data.forEach(d => {
     	columnNames.forEach(col => {
          d[col] = +d[col];
    	});
    });
    data.pop();
    return data;
  });

  const getCols = () =>
    d3.csv('http://vis.lab.djosix.com:2023/data/iris.csv').then(data => {
    const columnNames = Object.keys(data[0]);
    columnNames.pop();
    return columnNames;
  });

  let id = 1;
  const initBtn = (
    ButtonMenu,
    {
      columnNames
    }
  ) => {
    const xButtons = ButtonMenu.append('xButtons');
    xButtons.attr('class','item');
    xButtons.append('text').text('X-axis');
  	columnNames.forEach(col => {
      xButtons.append('br');
  		const xBt = xButtons
    		.append('span')
      	.attr('id',`xBt${id}`);
    	xBt
        .append('input')
      	.attr('type','radio')
      	.attr('name', 'xButton')
      	.property('checked',id==1)
        .on('change', function(){
          console.log("!!!");
          if (this.checked) {
          let xSelectedBt = this.parentNode.id; 
          switch(xSelectedBt){
            case 'xBt1': xV="sepal length";  break;
            case 'xBt2': xV="sepal width"; break;
            case 'xBt3': xV="petal length"; break;
            case 'xBt4': xV="petal width"; break;
          }
          console.log(xV);
          d3.select("svg").selectAll("*").remove();
          render(xV, yV);
        }


        });
      xBt
        .append('text')
      	.text(col);
      
      id +=1;
    });

    
    id=1;
    
    const yButtons = ButtonMenu.append('yButtons');
    yButtons.attr('class','item');
  	yButtons.append('text').text('Y-axis');
  	columnNames.forEach(col => {
      yButtons.append('br');
  		const yBt = yButtons
    		.append('span')
      	.attr('id',`yBt${id}`);
    	yBt
        .append('input')
      	.attr('type','radio')
      	.attr('name', 'yButton')
      	.property('checked',id==2)
        .on('change', function(){
          console.log("!!!");
          if (this.checked) {
          let ySelectedBt = this.parentNode.id; 
          switch(ySelectedBt){
            case 'yBt1': yV="sepal length";  break;
            case 'yBt2': yV="sepal width"; break;
            case 'yBt3': yV="petal length"; break;
            case 'yBt4': yV="petal width"; break;
          }
          console.log(yV);
          d3.select("svg").selectAll("*").remove();
          render(xV, yV);
        }


        });
      yBt
        .append('text')
      	.text(col);
      id+=1;
    });
    
  document.addEventListener('DOMContentLoaded', function() {
    const xRadioButtons = document.getElementsByName('xButton');
    const yRadioButtons = document.getElementsByName('yButton');
    
    // Add event listeners to radio buttons here
    xRadioButtons.forEach(xBtn => {
      xBtn.addEventListener('change', function(){
        console.log("!!!");
        if (this.checked) {
        let xSelectedBt = this.parentNode.id; 
        switch(xSelectedBt){
          case 'xBt1': xV="sepal length";  break;
          case 'xBt2': xV="sepal width"; break;
          case 'xBt3': xV="petal length"; break;
          case 'xBt4': xV="petal width"; break;
        }
        console.log(xV);
        d3.select("svg").selectAll("*").remove();
        render(xV, yV);
      }  });
    yRadioButtons.forEach(yBtn => {
      yBtn.addEventListener('change', function(){
        if (this.checked) {
        let ySelectedBt = this.parentNode.id; 
        switch(ySelectedBt){
          case 'yBt1': yV="sepal length";  break;
          case 'yBt2': yV="sepal width"; break;
          case 'yBt3': yV="petal length"; break;
          case 'yBt4': yV="petal width"; break;
          }
          console.log(yV);
          d3.select("svg").selectAll("*").remove();
          render(xV, yV);
        }    });
    });
  });
  });


  };

  const initLgd = (
    LegendMenu
  ) => {
    const legends = LegendMenu.append('legends');
    legends.attr('class','item');
    legends.append('text').text('Legends');

  	const Class = ['setosa','versicolor','virginica'];
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
      
  };

  const axes = (
    selection,
    { width, height, margin, xScale, yScale, xV, yV }
  ) => {
    const { top, right, bottom, left } = margin;
    selection
      .selectAll('g.axis-y')
      .data([null])
      .join('g')
      .attr('class', 'axis axis-y')
      .attr('transform', `translate(${left},0)`)
      .call(d3.axisLeft(yScale));
     selection
     	.append('text')
    	.attr('id','y-axis-label')
      .attr('transform','rotate(-90)')
      .attr('x',0-(height/2))
    	.attr('y',0.07* width)
      .attr('dy','1em')
      .attr('text-anchor','middle')
      .text(yV);

    selection
      .selectAll('g.axis-x')
      .data([null])
      .join('g')
      .attr('class', 'axis axis-x')
      .attr(
        'transform',
        `translate(0,${height - bottom})`
      )
      .call(d3.axisBottom(xScale));
    
    selection
      .append('text')
    	.attr('id','x-axis-label')
      .attr('x',width/2)
      .attr('y',0.99* height)
      .attr('text-anchor','middle')
      .text(xV);
  };

  const plot = (
    selection,
    {
      data,
      xValue,
      yValue,
      sValue,
      xV,
      yV,
      width,
      height,
      margin,
      circleRadius,
    }
  ) => {
    const { top, right, bottom, left } = margin;

    const xScale = d3.scaleLinear()
      .domain(d3.extent(data, xValue))
      .range([left, width - right]);

    const yScale = d3.scaleLinear()
      .domain(d3.extent(data, yValue))
      .range([height - bottom, top]);
    
    const marker = (d) =>{
      switch(d){
        case 'Iris-setosa': return '#85a3d4';
        case 'Iris-versicolor': return '#d485d4';
        case 'Iris-virginica': return '#edda82';
      }
    };

    selection
      .selectAll('circle')
      .data(data)
      .join('circle')
      .attr('r', circleRadius)
      .attr('fill', (d) =>marker(sValue(d)))
      .attr('cx', (d) => xScale(xValue(d)))
      .attr('cy', (d) => yScale(yValue(d)));
    

    axes(selection, {
      width,
      height,
      margin,
      xScale,
      yScale,
      xV,
      yV
    });
  };

  let xV='sepal length';
  let yV='sepal width';
  const width = window.innerWidth;
  const height = 0.9* window.innerHeight;

  const setBtn = async () => {
   const btn = d3.select('#ButtonMenu')
      .attr('width', 0.3* width)
      .attr('height', height)
    	.call(initBtn,{
      	columnNames: await getCols(),
        
      });
  };

  const setLegend = async () => {
   const legend= d3.select('#LegendMenu')
      .attr('width', 0.3* width)
      .attr('height', height)
    	.call(initLgd);
  };

  const svg = d3.select('#svg')
    .append('svg')
    .attr('id','svg');

  const render = async (xV,yV) => {

    svg
      .attr('width', 0.7* width)
      .attr('height', height)
      .call(plot, {
        data: await loadData(),
        xValue: (d) => d[xV],
        yValue: (d) => d[yV],
      	sValue: (d) => d['class'],
      	xV: xV,
      	yV: yV,
        width: 0.7 * width,
        height: height,
        margin: {
          top: 0.1* height,
          right: 0.1 * width,
          bottom: 0.15* height,
          left: 0.15* width
        },
        circleRadius: 5,
      });
  };
  setBtn();
  setLegend();
  render(xV,yV);




}(d3));
