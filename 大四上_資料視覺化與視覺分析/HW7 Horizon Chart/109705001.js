(function () {
  'use strict';

  //外框變數定義
  const width = window.innerWidth;
  const height = window.innerHeight;
  const marginOut = {left: 0, right: 0, top: 30, bottom: 10};
  const sizeOut_x = width - marginOut.left- marginOut.right;
  const sizeOut_y = height - marginOut.top - marginOut.bottom;

  const svg = d3.select('svg')
      .attr('height', height*3)
      .attr('width', sizeOut_x + marginOut.left + marginOut.right)
      .append('g')
      .attr('transform', `translate(${marginOut.left}, ${marginOut.top})`);

  //horizon chart所需之顏色、分層
  const color_scheme = [d3.schemeBlues, d3.schemeReds, d3.schemeGreens,
    d3.schemePurples, d3.schemeOranges, d3.schemeGreys];
  var bands =5;
  //下拉式選單決定呈現的圖
  const compareSelect = d3.select('#compare');
  const pollutantSelect = d3.select('#pollutant');
  const stationSelect = d3.select('#stationCode');
  const yearSelect = d3.select('#year');
  var selectedYear = 'all';
  var flag=-1;

  const text1 = d3.select("#text1");
  const text2 = d3.select("#text2");
  const text3 = d3.select("#text3");

  //畫圖
  const render = (data__,Stations,pollutantNames,maxValues,flag,selectedYear) => {

    	/*parameters: 
        data_:[[date,station, pollutant1~6]]
    	  Stations: 101~125
    	  pollutantNames:SO2~PM2.5
    	  flag: -1: overall, 
        			0~5: compare different station in pollutant[flag]
              101~125: compare different pollutant station[flag]*/  

    	/* flag:0~5
      	 =>比較不同station的某汙染物 
         =>只要畫pollutantNames[flag]就好*/
    	var col_f = (flag >= 0 && flag < 6) ? pollutantNames.slice(flag, flag+1) : pollutantNames;

    	//子圖的數量 與寬度
  		var numCols = col_f.length;
    
    	/* flag:101~125
      	 =>比較同station的不同汙染物 
         =>垂直作畫 => subplotWidth = width*/
      const subplotWidth = (flag >= 101 && flag <= 125) ? width : sizeOut_x / col_f.length;
    	//horizon chart的高度
      const size = 50;
      const padding = 5;
      var margin = {
          top: (flag >= 101 && flag <= 125) ? size/2:50,
          right: 10,
          bottom: 0,
          left: 0,
        }
      
      //子圖的位置
      var plotPos_x = d3.scalePoint()
          .domain(col_f)
          .range([0, sizeOut_x - subplotWidth]);
    	//子圖的label
      svg.selectAll(".x-axis-label")
        .data((flag >= 101 && flag <= 125) ? [flag] : col_f)
        .enter()
        .append("text")
        .attr("class", "x-axis-label")
        .attr("x", (d) => (flag >= 101 && flag <= 125) ? width / 2 : plotPos_x(d) + subplotWidth / 2)
        .attr("y", -10)
        .text((d) => (flag >= 101 && flag <= 125) ? d : d)
        .style("text-anchor", "middle")
        .style("font-size", "0.8em")
        .style("fill", "#696969");


    
  		var data_ = data__;
      if (selectedYear !== 'all') {
        data_ = data__.filter(item => {
          const measurementYear = item['time'].getFullYear().toString();
          return measurementYear == selectedYear;
        });
      }
      /* flag:101~125
       =>比較同station的不同汙染物 
       =>只要篩出該station的資料來畫即可*/
    	const filteredData = (flag >= 101 && flag <= 125) ?
            data_.filter(item => item['Station code'] === flag.toString()) : data_;
    
   
    	//針對每一個子圖(汙染物)畫圖
      for (var i in col_f) {
        	// flag:0~5 index是該汙染物
        	if (flag >= 0 && flag < 6) i = flag;
        
        	// flag:101~125 是垂直作畫 其他是水平排列
        	const tmp1 = svg
    			.append('g')
    			.attr("transform", flag >= 101 && flag <= 125 ? 
                `translate(0,${i * size + margin.top})` : `translate(${plotPos_x(pollutantNames[i])},${0})`);
        
          //horizon chart的顏色依汙染物而不同
          var colors = color_scheme[i][Math.max(3, bands)].slice(Math.max(0, 3 - bands)); 
        
        	
        	//準備畫horizon chart的資料
          var data = filteredData.map(function(item) {
            return {
              'station': item['Station code'],
              'time': item['time'],
              'value': item[pollutantNames[i]]
            };
          });    	
          const series = d3.rollup(data, (values, i) => d3.sort(values, d => d.time), d => d.station);

          //x:時間軸
          const x = d3.scaleUtc()
            .domain(d3.extent(data, d => d.time))
            .range([0, subplotWidth]);

          //y:最大值是該汙染物在全部data裡的max
          const y = d3.scaleLinear()
            .domain([0,maxValues[pollutantNames[i]]])
            .range([size, size - bands * (size - padding)]);
        
          const area = d3.area()
            .defined(d => !isNaN(d.value))
            .x((d) => x(d.time))
            .y0(size)
            .y1((d) => y(d.value));

          const uid = `O-${Math.random().toString(16).slice(2)}`;

          tmp1 
            .attr("viewBox", [0, 0, width, height])
            .attr("style", "max-width: 100%; height: auto; font: 10px sans-serif;");

          const g = tmp1.append("g")
            .selectAll("g")
            .data(series)
            .join("g")
              .attr("transform", (d, i) => `translate(0,${i * size + margin.top})`);


          const defs = g.append("defs");
          defs.append("clipPath")
              .attr("id", (_, i) => `${uid}-clip-${i}`)
            .append("rect")
              .attr("y", padding)
              .attr("width", width)
              .attr("height", size - padding);

          defs.append("path")
            .attr("id", (_, i) => `${uid}-path-${i}`)
            .attr("d", ([, values]) => area(values));

          g.append("g")
            .attr("clip-path", (_, i) => `url(${new URL(`#${uid}-clip-${i}`, location)})`)
            .selectAll("use")
            .data((_ ,i) => new Array(bands).fill(i))
            .enter().append("use")
              .attr("xlink:href", (i) => `${new URL(`#${uid}-path-${i}`, location)}`)
              .attr("fill", (_, i) => colors[i])
              .attr("transform", (_, i) => `translate(0,${i * size})`);

          g.append("text")
              .attr("x", 4)
              .attr("y", (size + padding) / 2)
              .attr("dy", "0.35em")
              .text(([name])=>(flag >= 101 && flag <= 125) ? pollutantNames[i] : name);

            svg.append("g")
              .attr("transform", `translate(${(plotPos_x(pollutantNames[i]))},${55})`) // 原代码中使用了pollutantNames.length * size，这里改成5
              .call(d3.axisTop(x).ticks(width / 80).tickSizeOuter(0))
              .call(g => g.selectAll(".tick text") 
                .attr("transform", "rotate(-90) translate(10, 20)")
                .style("text-anchor", "start") 
                .style("dy", "1em"))
              .call(g => g.selectAll(".tick").filter(d => x(d) < margin.left || x(d) >= width - margin.right).remove())
              .call(g => g.select(".domain").remove());
            
            svg.append("g")
              .attr("transform", `translate(${plotPos_x(pollutantNames[i])},${flag >= 101 && flag <= 125 ? 55 + 6 * size : 55 + Stations.length * size})`) 
              .call(d3.axisTop(x).ticks(width / 80).tickSizeOuter(0))
              .call(g => g.selectAll(".tick text") 
                .attr("transform", "rotate(-90) translate(0, 20)")
                .style("text-anchor", "end") 
                .style("dy", "1em"))
              .call(g => g.selectAll(".tick").filter(d => x(d) < margin.left || x(d) >= width - margin.right).remove())
              .call(g => g.select(".domain").remove());
            
        }
    
    //下拉式選單=================================================================================
    compareSelect.on('change', function() {
    	const selectedOption = compareSelect.property('value');
    
      if (selectedOption === 'all') {
        text1.text("This is the overview of the data");
      	text2.text("If you want to compare the same pollutant in different stations, please select 'between stations'");
      	text3.text("If you want to compare different pollutants in one station, please select 'in one station'");
      
        d3.select('#pollutantDiv').style('display', 'none');
        d3.select('#stationCodeDiv').style('display', 'none');
        svg.selectAll("*").remove();
        flag = -1;
        render(data__,Stations,pollutantNames,maxValues,flag, selectedYear);
        
      } else if (selectedOption === 'between stations') {
        
        text1.text("Please choose the pollutant you want to compare");
      	text2.text(" ");
      	text3.text(" ");
        d3.select('#pollutantDiv').style('display', 'block');
        d3.select('#stationCodeDiv').style('display', 'none');
        svg.selectAll("*").remove();
        flag = +pollutantSelect.property('value');
        render(data__,Stations,pollutantNames,maxValues,flag, selectedYear);
        
      } else if (selectedOption === 'in one station') {
        text1.text("Please choose the station you want to compare");
      	text2.text(" ");
      	text3.text(" ");
        d3.select('#pollutantDiv').style('display', 'none');
        d3.select('#stationCodeDiv').style('display', 'block');
        svg.selectAll("*").remove();
        flag = +stationSelect.property('value');
        render(data__,Stations,pollutantNames,maxValues,flag, selectedYear);
      }
    });
    
    pollutantSelect.on('change', function() {
      flag = +pollutantSelect.property('value');
      svg.selectAll("*").remove();
      render(data__,Stations,pollutantNames,maxValues,flag, selectedYear);
    });
    
    stationSelect.on('change', function() {
      flag = +stationSelect.property('value');
      svg.selectAll("*").remove();
      render(data__,Stations,pollutantNames,maxValues,flag, selectedYear);
    });
    
    yearSelect.on('change', function () {
      selectedYear = yearSelect.property('value');
      svg.selectAll('*').remove();
      render(data__, Stations, pollutantNames, maxValues, flag, selectedYear);
    });
  };

  var pollutantNames = ["SO2", "NO2", "CO", "O3", "PM10", "PM2.5"];
  d3.csv('http://vis.lab.djosix.com:2023/data/air-pollution.csv').then(function (data) {
  console.log('start');
  var Stations = Array.from(new Set(data.map(d => d["Station code"])));
    var groupedData = d3.nest()
    .key(function(d) { return d["Measurement date"].split(" ")[0] + d["Station code"]; })
    .rollup(function(d) {
      //先清掉missing value -1
      function filterAndParseFloat(arr, key, minRange, maxRange) {
        return arr
          .filter(function (item) {
            var value = parseFloat(item[key]);
            return !isNaN(value) && value >= minRange && value <= maxRange;
          })
          .map(function (item) {
            return parseFloat(item[key]);
          });
      }

      var SO2 = filterAndParseFloat(d, 'SO2', 0, 0.01);
      var NO2 = filterAndParseFloat(d, 'NO2', 0, 0.1);
      var O3 = filterAndParseFloat(d, 'O3', 0, 0.1);
      var CO = filterAndParseFloat(d, 'CO', 0, 2);
      var PM10 = filterAndParseFloat(d, 'PM10', 0, 100);
      var PM2_5 = filterAndParseFloat(d, 'PM2.5', 0, 100);

      return {
        'time': new Date(d[0]['Measurement date'].split(" ")[0]),
        'Station code': d[0]['Station code'],
        'SO2': SO2.length > 0 ? +(d3.mean(SO2).toFixed(4)) : 0,
        'NO2': NO2.length > 0 ? +(d3.mean(NO2).toFixed(4)) : 0,
        'O3': O3.length > 0 ? +(d3.mean(O3).toFixed(4)) : 0,
        'CO': CO.length > 0 ? +(d3.mean(CO).toFixed(4)) : 0,
        'PM10': PM10.length > 0 ? +(d3.mean(PM10).toFixed(4)) : 0,
        'PM2.5': PM2_5.length > 0 ? +(d3.mean(PM2_5).toFixed(4)) : 0,
      };
    })
    .entries(data);


    data = groupedData.map(function(item) {
      return item.value;
    });
    const maxValues = {'SO2':0.01,'NO2':0.1,'O3':0.1,"CO":2,"PM10":100,"PM2.5":100};

    text1.text("This is the overview of the data");
    text2.text("If you want to compare the same pollutant in different stations, please select 'between stations'");
    text3.text("If you want to compare different pollutants in one station, please select 'in one station'");
      
    render(data,Stations,pollutantNames,maxValues,flag,selectedYear);

  });

}());

