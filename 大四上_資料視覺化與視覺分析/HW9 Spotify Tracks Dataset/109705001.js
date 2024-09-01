//global data
var globalData;
var globalGenre;

//svg
var margin = {top: 0, right: 0, bottom: 0, left: 0},
    width = window.innerWidth -margin.left - margin.right,
    height = window.innerHeight -margin.top - margin.bottom;

var svgContainer = d3.select("#svg-container");

//bar plot
var headInput = d3.select("#head");
var head = +headInput.property("value");
var tailInput = d3.select("#tail");
var tail = +tailInput.property("value");
var bar_flag = "all";
var bar_gen_flag= "all";
var ana_gen_flag = "all";
var ana_flag ="G";

const color_keys = [
  'track_name','artists','albumn','buy_low'
];


var color = d3
  .scaleOrdinal()
  .domain(color_keys)
  .range(d3.schemeTableau10);


//畫bar chart===============================================================
const RenderBarChart = (svg_container,data_, head, tail,x_att,y_att) =>{
  const inner_margin = {top: 10, right: 30, bottom: 100, left: 30},
    inner_width = width - inner_margin.left - inner_margin.right,
    inner_height = height*0.4 - inner_margin.top - inner_margin.bottom;
  
  
  var svg_ = svg_container 
  			.append('svg')
        .attr("width", width)
        .attr("height", height*0.4)
  			.append("g")
          .attr("transform", `translate(${inner_margin.left},${inner_margin.top})`);
  svg_
    .append('text')
    .text(`Rank for ${x_att}`)
  	.attr('id','BarPlotHead')
    .attr("transform", `translate(${-20}, ${10})`) // Adjust the position as needed
    .style("text-anchor", "start"); 
  
  var header_h = 30;

  var data__ = data_.sort(function(b, a) {
    return a[y_att] - b[y_att];
  });  
  if(x_att==='track_name')
  {
    //只顯示head~tail的資料
    extendedData= data__.slice(head-1, tail*3);

    const uniqueData = Array.from(new Set(extendedData.map(item => item.track_name)))
      .map(track_name => extendedData.find(item => item.track_name === track_name));

    // Sort the unique data by 'popularity'
    data__ = uniqueData.sort((a, b) => b[y_att] - a[y_att]).slice(0, tail - head + 1); 
  }
  else
  {
    data__ =data__.slice(head-1, tail); 
  }
  
  //x軸都有誰
  const x = d3.scaleBand()
    .range([ 0, inner_width])
    .domain(data__.map(d => d[x_att]))
    .padding(0.2);
  
  svg_.append("g")
    .attr("transform", `translate(0, ${inner_height+header_h})`)
    .call(d3.axisBottom(x))
    .selectAll("text")
      .attr("transform", "translate(-10,0)rotate(45)")
      .style("text-anchor", "start");

  // Add Y axis
  const y = d3.scaleLinear()
    .domain([0, 100])
    .range([ inner_height+header_h, header_h]);
  svg_.append("g")
    .call(d3.axisLeft(y));

  // Bars
  svg_.selectAll("mybar")
    .data(data__)
    .join("rect")
      .attr("x", d => x(d[x_att]))
      .attr("y", d => y(d[y_att]))
      .attr("width", x.bandwidth())
      .attr("height", d => inner_height - y(d[y_att]) + header_h)
      .attr("fill", color(x_att))
      .each(function (d) {
        d3.select(this)
          .on("mouseover", function (event) {
            d3.select(this).attr("stroke", "red");
            const tooltipWidth = tooltip.node().offsetWidth;
            const tooltipX = Math.min(event.pageX, window.innerWidth - tooltipWidth - 30);
            tooltip.transition()
              .duration(200)
              .style("opacity", .9);
      
            if (x_att === 'track_name') {
              tooltip.html(`<strong>${d[x_att]}</strong><br>
                             Popularity: ${d[y_att]}<br>
                             Artist: ${d.artists}<br>
                             Album: ${d.album_name}<br>
                             Genre: ${d.track_genre}`);
            } else {
              tooltip.html(`<strong>${d[x_att]}</strong><br>
                             Popularity: ${d[y_att]}<br>`);
            }
      
            tooltip.style("left", (tooltipX) + "px")
              .style("top", (event.pageY - 28) + "px");
          })
          .on("mouseout", function () {
            d3.select(this).attr("stroke", "none");
            tooltip.transition()
              .duration(500)
              .style("opacity", 0);
          });
      });
      
  
  const tooltip = d3.select("body")
    .append("div")
    .attr("class", "tooltip")
    .style("opacity", 0);
}


//總排名=====================================================================
const Leaderboard = () =>{
  var svg1_container = svgContainer
    .append('xhtml:div')
    .style("margin-bottom", "10px");

  var svg2_container = svgContainer
    .append('xhtml:div')
    .style("margin-bottom", "10px");

  var svg3_container = svgContainer
    .append('xhtml:div')
    .style("margin-bottom", "10px");
	
  var svg4_container = svgContainer
      .append('xhtml:div')
      .style("margin-bottom", "10px");
  
  var data_draw = globalData
  if(bar_flag!="all")
  {
     data_draw= data_draw.filter(function(d) {
        return d.track_genre === bar_gen_flag;
    	});
  }

  // Get required data (artists, album_name, track_name, popularity)
  var data_tmp = data_draw.map(function(d) {
    return {
      artists: d.artists,
      album_name: d.album_name,
      track_name: d.track_name,
      track_genre:d.track_genre,
      popularity: d.popularity
    };
  });
  console.log(data_tmp )

  // Group by artists and calculate average popularity
  var data_artist = d3.rollup(data_tmp, v => d3.mean(v, d => +d.popularity), d => d.artists);
  data_artist = Array.from(data_artist, ([key, value]) => ({ artists: key, popularity: value }));

  // Group by albumn and calculate average popularity
  var data_albumn = d3.rollup(data_tmp, v => d3.mean(v, d => +d.popularity), d => d.album_name);
  data_albumn = Array.from(data_albumn, ([key, value]) => ({ albumn: key, popularity: value }));
  
  var data_genre = d3.rollup(data_tmp, v => d3.mean(v, d => +d.popularity), d => d.track_genre);
  data_genre = Array.from(data_genre, ([key, value]) => ({ genre: key, popularity: value }));
  
  RenderBarChart(svg1_container,data_tmp, head, tail,"track_name","popularity")
  RenderBarChart(svg2_container,data_artist, head, tail,"artists","popularity")
  RenderBarChart(svg3_container,data_albumn, head, tail,"albumn","popularity")
  if(bar_flag=="all"){
  	RenderBarChart(svg4_container,data_genre, head, tail,"genre","popularity")
  }
  
  headInput.on("input", function () {
    	d3.select("#Leaderboard").property("checked", true);
      if (+headInput.property("value") <= tail) {
          head = +headInput.property("value");
          svgContainer.selectAll('*').remove();
          Leaderboard();
      } else {
          headInput.property("value", tail);
      }
  });

  tailInput.on("input", function () {    
    	d3.select("#Leaderboard").property("checked", true);
      if (+tailInput.property("value") >= head) {
          tail = +tailInput.property("value");
          svgContainer.selectAll('*').remove();
          Leaderboard();
      } else {
          tailInput.property("value", head);
      }
  });
  
}

// 雷達圖 ===================================================================
function RenderRadarChart(id, data,genre,pop, w_) {
    var cfg = {
        margin: {top: 60, right: 30, bottom: 30, left:30},
      	w: w_*0.7,
        h: w_*0.7,
        levels: 5,
        labelFactor: 1.19,
        wrapWidth: 60,
        dotRadius: 3,
        strokeWidth: 2,
        roundStrokes: false,
        color: '#4e79a7'
    };
    var maxValue = 1;
  	var color = cfg.color;
    var allAxis = (data[0].map(function (i, j) {
            return i.axis
        })),
        total = allAxis.length,
        radius = Math.min(cfg.w / 2, cfg.h / 2),
        Format = d3.format(".0%"),
        angleSlice = Math.PI * 2 / total;

    var rScale = d3.scaleLinear()
        .range([0, radius])
        .domain([0, maxValue]);

    d3.select(id).select("svg").remove();

    var svg = d3.select(id).append("svg")
        .attr("width", cfg.w + cfg.margin.left + cfg.margin.right)
        .attr("height", cfg.h + cfg.margin.top + cfg.margin.bottom)
        .attr("class", "radar");
  	
  	svg.append("text")
      .attr("class", "chart-title")
      .attr("x", cfg.w / 2 + cfg.margin.left)
      .attr("y", cfg.margin.top / 2)
      .attr("text-anchor", "middle")
      .style("font-size", "16px")
      .style("font-weight", "bold")
      .text(`${genre}${pop}`);


    var g = svg.append("g")
        .attr("transform", "translate(" + (cfg.w / 2 + cfg.margin.left) + "," + (cfg.h / 2 + cfg.margin.top) + ")");
  	
  	//一圈一圈
    var axisGrid = g.append("g").attr("class", "axisWrapper");

    axisGrid.selectAll(".levels")
        .data(d3.range(1, (cfg.levels + 1)).reverse())
        .enter()
        .append("circle")
        .attr("class", "gridCircle")
        .attr("r", function (d, i) {
            return radius / cfg.levels * d;
        })
        .style("fill", "#ffffff")
        .style("stroke", "#cccccc");

    axisGrid.selectAll(".axisLabel")
        .data(d3.range(1, (cfg.levels + 1)).reverse())
        .enter().append("text")
        .attr("class", "axisLabel")
        .attr("x", 4)
        .attr("y", function (d) {
            return -d * radius / cfg.levels;
        })
        .attr("dy", "0.4em")
        .style("font-size", "10px")
        .attr("fill", "#737373")
        .text(function (d, i) {
            return Format(maxValue * d / cfg.levels);
        });

    var axis = axisGrid.selectAll(".axis")
        .data(allAxis)
        .enter()
        .append("g")
        .attr("class", "axis");

    axis.append("line")
        .attr("x1", 0)
        .attr("y1", 0)
        .attr("x2", function (d, i) {
            return rScale(maxValue * 1.1) * Math.cos(angleSlice * i - Math.PI / 2);
        })
        .attr("y2", function (d, i) {
            return rScale(maxValue * 1.1) * Math.sin(angleSlice * i - Math.PI / 2);
        })
        .attr("class", "line")
        .style("stroke", "#848484")
        .style("stroke-width", "1px");

    axis.append("text")
        .attr("class", "legend")
        .style("font-size", "11px")
        .attr("text-anchor", "middle")
        .attr("dy", "0.35em")
        .attr("x", function (d, i) {
            return rScale(maxValue * cfg.labelFactor) * Math.cos(angleSlice * i - Math.PI / 2);
        })
        .attr("y", function (d, i) {
            return rScale(maxValue * cfg.labelFactor) * Math.sin(angleSlice * i - Math.PI / 2);
        })
        .text(function (d) {
            return d
        })
        .call(wrap, cfg.wrapWidth);

    var blobWrapper = g.selectAll(".radarWrapper")
        .data(data)
        .enter().append("g")
        .attr("class", "radarWrapper");

    blobWrapper
        .append("path")
        .attr("class", "radarArea")
        .attr("d", function (d, i) {
            return radarLine(d);
        })
        .style("fill", color)
        .style("fill-opacity", 0.5);
        

    blobWrapper.append("path")
        .attr("class", "radarStroke")
        .attr("d", function (d, i) {
            return radarLine(d);
        })
        .style("stroke-width", cfg.strokeWidth + "px")
        .style("stroke", color)
        .style("fill", "none");

    var blobCircleWrapper = g.selectAll(".radarCircleWrapper")
        .data(data)
        .enter().append("g")
        .attr("class", "radarCircleWrapper");

    blobCircleWrapper.selectAll(".radarInvisibleCircle")
        .data(function (d, i) {
            return d;
        })
        .enter().append("circle")
        .attr("class", "radarInvisibleCircle")
        .attr("r", cfg.dotRadius )
        .attr("cx", function (d, i) {
            return rScale(d.value) * Math.cos(angleSlice * i - Math.PI / 2);
        })
        .attr("cy", function (d, i) {
            return rScale(d.value) * Math.sin(angleSlice * i - Math.PI / 2);
        })
        .style("fill", color)
        .style("pointer-events", "all")
        .on("mouseover", function (d, i) {
            let newX = parseFloat(d3.select(this).attr('cx')) - 10;
            let newY = parseFloat(d3.select(this).attr('cy')) - 10;

            tooltip
                .attr('x', newX)
                .attr('y', newY)
                .text(Format(d3.select(this).datum().value))
                .transition().duration(200)
                .style('opacity', 1);
        })
        .on("mouseout", function () {
            tooltip.transition().duration(200)
                .style("opacity", 0);
        });

    var tooltip = g.append("text")
        .attr("class", "tooltip")
        .style("opacity", 0);

    function wrap(text, width) {
        text.each(function () {
            var text = d3.select(this),
                words = text.text().split(/\s+/).reverse(),
                word,
                line = [],
                lineNumber = 0,
                lineHeight = 1.4,
                y = text.attr("y"),
                x = text.attr("x"),
                dy = parseFloat(text.attr("dy")),
                tspan = text.text(null).append("tspan").attr("x", x).attr("y", y).attr("dy", dy + "em");

            while (word = words.pop()) {
                line.push(word);
                tspan.text(line.join(" "));
                if (tspan.node().getComputedTextLength() > width) {
                    line.pop();
                    tspan.text(line.join(" "));
                    line = [word];
                    tspan = text.append("tspan").attr("x", x).attr("y", y).attr("dy", ++lineNumber * lineHeight + dy + "em").text(word);
                }
            }
        });
    }

    function radarLine(d) {
        return d3.radialLine()
            .radius(function (d) {
                return rScale(d.value);
            })
            .angle(function (d, i) {
                return i * angleSlice;
            })
            .curve(d3.curveLinearClosed)(d);
    }
}
// 音樂分析==================================================================
function AnalysisAll() {
  const groupedData = d3.group(globalData, (d) => d.track_genre);
  
  const numCols = 7;

  const divWidth = window.innerWidth * 0.96 / (numCols);
  var Averages = [];
  
  groupedData.forEach((genreData, genre, index) => {
    const averages = [];
    const avgDanceability = d3.mean(genreData, (d) => d.danceability);
    const avgEnergy = d3.mean(genreData, (d) => d.energy);
    const avgSpeechiness = d3.mean(genreData, (d) => d.speechiness);
    const avgAcousticness = d3.mean(genreData, (d) => d.acousticness);
    const avgInstrumentalness = d3.mean(genreData, (d) => d.instrumentalness);
    const avgLiveness = d3.mean(genreData, (d) => d.liveness);
    const avgValence = d3.mean(genreData, (d) => d.valence);
    const avgPopularity = d3.mean(genreData, (d) => d.popularity).toFixed(2);

    averages.push(
      { axis: 'instrumental', value: avgInstrumentalness },
      { axis: 'live', value: avgLiveness },
      { axis: 'valence', value: avgValence },
      { axis: 'danceable', value: avgDanceability },
      { axis: 'energy', value: avgEnergy },
      { axis: 'speech', value: avgSpeechiness },
      { axis: 'acoustic', value: avgAcousticness },      
      
      
    );
    var idx =  generateIndex(averages);
    
    Averages.push({
      gen: genre,
      pop: avgPopularity,
      data: [averages],
      index:idx
    })
  });

  if(ana_flag==='G')
  {
  	Averages = Averages.slice().sort((a, b) => a.gen.localeCompare(b.gen));
  }
  else if (ana_flag==='P')
  {
  	Averages = Averages.slice().sort((a, b) => b.pop - a.pop);
  }
  else if (ana_flag==='I')
  {
  	Averages = Averages.slice().sort((a, b) => b.index - a.index);
  }
  for (const genre in Averages) {
    const div = svgContainer
      .append("div")
      .style("width", divWidth + "px")
      .style("display", "inline-block")
      .attr("class", "radar-chart-div");
    
    RenderRadarChart(
      div.node(),
      Averages[genre].data, 
      Averages[genre].gen,     
      `: ${Averages[genre].pop}`,    
      divWidth
    );
  }
  
	function generateIndex(avg) {
      // Assuming avg is an array of objects
      var avgObj = {};
      avg.forEach(item => {
          avgObj[item.axis] = item.value;
      });
      var idx=0
      if (avgObj['instrumental'] < 0.15 && avgObj['acoustic'] > 0.40 && avgObj['speech'] < 0.15){idx = 7;}
      else if (avgObj['instrumental'] < 0.15 && avgObj['acoustic'] > 0.25 && avgObj['speech'] < 0.15){idx = 6;}
      else if (avgObj['instrumental'] > 0.40 && avgObj['acoustic'] < 0.20 && avgObj['live'] < 0.20) {idx = 5;}
      else if (avgObj['instrumental'] >= 0.30 && avgObj['acoustic'] >= 0.30){idx=4;}   
      else if (avgObj['instrumental'] >= 0.20 && avgObj['acoustic'] >= 0.20){idx=3;}  
      else if (avgObj['energy'] >=0.60 && avgObj['danceable'] <=0.50){idx = 2;}
      else if (avgObj['instrumental'] <= 0.30 && avgObj['acoustic'] <= 0.30){idx = 1;}
      return idx;
  }
  
}
 



// 曲風簡介==================================================================
function RenderDiscript(svg_container, data_, width) {
  const inner_margin = { top: 20, right: 30, bottom: 100, left: 30 },
    inner_width = width - inner_margin.left - inner_margin.right,
    inner_height = height * 0.4 - inner_margin.top - inner_margin.bottom;

  const svg_ = svg_container
    .append('svg')
    .attr('width', width)
    .attr('height', height * 0.4)
    .append('g')
    .attr('transform', `translate(${inner_margin.left},${inner_margin.top})`);

  const y = d3.scaleLinear()
    .domain([0, 5])
    .range([0, inner_height]);

  const line_height = 30; 
  const indent = 20; 

  svg_.append('text')
    .attr('x', 0)
    .attr('y', line_height) 
    .attr('text-anchor', 'start')
    .style('font-size', '2em')
    .style('font-weight', 'bold')
    .text(ana_gen_flag);


  function appendIndentedText(id, text, value) {
    const numeric_value = typeof value === 'number' ? value : parseFloat(value);
    const y_offset = y(id) + 2 * line_height + id*6;

    svg_.append('text')
      .attr('x', indent) 
      .attr('y', y_offset)
      .attr('text-anchor', 'start')
      .style('font-size', '1.5em')
      .style('line-height', line_height)
      .text(`${text}: ${numeric_value.toFixed(2)}`);
  }

  // 添加缩进的文本，依次添加
  appendIndentedText(0, 'Number of songs', data_.song_num);
  appendIndentedText(1, 'Average popularity', data_.avg_popularity);
  appendIndentedText(2, 'Average tempo(BPM)', data_.avg_tempo);
  appendIndentedText(3, 'Average loudness(DB)', data_.avg_loudness);
  appendIndentedText(4, 'Major key', data_.major_key);
  appendIndentedText(5, 'Major time signature', data_.major_time_sign);
}
// Single Analysis histogram =====================================================
const RenderHistChart = (svg_container,data_,title,x_att,w,h) =>{
  const inner_margin = {top: 10, right: 30, bottom: 105, left: 30},
    inner_width = w- inner_margin.left - inner_margin.right,
    inner_height = height*0.4 - inner_margin.top - inner_margin.bottom;
  var svg_ = svg_container 
  			.append('svg')
        .attr("width", w)
        .attr("height", height*0.4)
  			.append("g")
          .attr("transform", `translate(${inner_margin.left},${inner_margin.top})`);
  svg_
    .append('text')
    .text(title)
  	.attr('id','BarPlotHead')
    .attr("transform", `translate(${-20}, ${10})`) // Adjust the position as needed
    .style("text-anchor", "start"); 
  
  var header_h = 30;
  
  var x = d3.scaleLinear()
    .domain([d3.min(data_, (d)=> +d[x_att]), d3.max(data_, (d)=> +d[x_att])])
    .range([0, inner_width]);
  
  svg_.append("g")
      .attr("transform", `translate(0, ${inner_height+header_h})`)
      .call(d3.axisBottom(x));

  // set the parameters for the histogram
  var histogram = d3.histogram()
      .value(function(d) { return d[x_att]; }) 
      .domain(x.domain()) 
      .thresholds(x.ticks(10)); 
  // And apply this function to data to get the bins
  var bins = histogram(data_);

  // Y axis: scale and draw:
  var y = d3.scaleLinear()
      .range([ inner_height+header_h, header_h]);
      y.domain([0, d3.max(bins, function(d) { return d.length; })]);  
  svg_.append("g")
      .call(d3.axisLeft(y).ticks(5));
  // append the bar rectangles to the svg element
  svg_.selectAll("rect")
      .data(bins)
      .enter()
      .append("rect")
        .attr("x", 1)
        .attr("transform", function(d) { return "translate(" + x(d.x0) + "," + y(d.length) + ")"; })
        .attr("width", function(d) { return x(d.x1) - x(d.x0) -1 ; })
        .attr("height", function(d) { return inner_height - y(d.length)+header_h; })
        .style("fill", '#4e79a7')
}

// single Analysis bar char=======================================================
const ARenderBarChart = (svg_container,data_,title,x_att,y_att,w,h) =>{
  const inner_margin = {top: 10, right: 30, bottom: 100, left: 30},
    inner_width = w- inner_margin.left - inner_margin.right,
    inner_height = height*0.4 - inner_margin.top - inner_margin.bottom;
  var svg_ = svg_container 
  			.append('svg')
        .attr("width", w)
        .attr("height", height*0.4)
  			.append("g")
          .attr("transform", `translate(${inner_margin.left},${inner_margin.top})`);
  svg_
    .append('text')
    .text(title)
  	.attr('id','BarPlotHead')
    .attr("transform", `translate(${-20}, ${10})`) // Adjust the position as needed
    .style("text-anchor", "start"); 
  
  var header_h = 30;
  
  //x軸都有誰
  const x = d3.scaleBand()
    .range([ 0, inner_width])
    .domain(data_.map(d => d[x_att]))
    .padding(0.2);
  
  svg_.append("g")
    .attr("transform", `translate(0, ${inner_height+header_h})`)
    .call(d3.axisBottom(x))
    .selectAll("text")
      .style("text-anchor", "center");

  // Add Y axis
  const y = d3.scaleLinear()
    .domain([0, d3.max(data_, d => d.count)])
    .range([ inner_height+header_h, header_h]);
  svg_.append("g")
    .call(d3.axisLeft(y));

  // Bars
  svg_.selectAll("mybar")
    .data(data_)
    .join("rect")
      .attr("x", d => x(d[x_att]))
      .attr("y", d => y(d[y_att]))
      .attr("width", x.bandwidth())
      .attr("height", d => inner_height - y(d[y_att])+header_h)
      .attr("fill", '#4e79a7')
}
// 曲風分析=================================================================
function SingleAnalysis() {
  // Filter data based on the genre flag
  var data_tmp = globalData.filter(d => d.track_genre === ana_gen_flag);

  // Calculate summary statistics
  var data_text = {
    song_num: data_tmp.length,
    avg_tempo: d3.mean(data_tmp, d => d.tempo),
    major_key: getMode(data_tmp.map(d => d.key)),
    major_time_sign: getMode(data_tmp.map(d => d.time_signature)),
    avg_loudness: d3.mean(data_tmp, d => d.loudness),
    avg_popularity: d3.mean(data_tmp, d => d.popularity),
  };

  // Prepare data for histograms and bar charts
  var hist_attributes = ['popularity', 'loudness', 'tempo'];
  
  var data_hist = hist_attributes.map(attribute => {
    return {
      key: attribute,
      data: data_tmp.map(d => ({ value: d[attribute] })),
    };
  });
  
  console.log("data_hist",data_hist)
	
  var bar_attributes = ['explicit', 'mode', 'key', 'time_signature'];
  var data_bar = {};

  var data_bar = bar_attributes.map(attribute => {
    // Count occurrences of each unique category
    var countByCategory = d3.rollup(
      data_tmp,
      v => v.length,
      d => d[attribute]
    );

    // Convert the map to an array of objects
    var data = Array.from(countByCategory, ([category, count]) => ({ category, count }));

    // Step 3: Sort the data in ascending order of counts
    data.sort((a, b) => a.category - b.category);

    return { key: attribute, data };
  });



  const averages = [];
  const avgDanceability = d3.mean(data_tmp, (d) => d.danceability);
  const avgEnergy = d3.mean(data_tmp, (d) => d.energy);
  const avgSpeechiness = d3.mean(data_tmp, (d) => d.speechiness);
  const avgAcousticness = d3.mean(data_tmp, (d) => d.acousticness);
  const avgInstrumentalness = d3.mean(data_tmp, (d) => d.instrumentalness);
  const avgLiveness = d3.mean(data_tmp, (d) => d.liveness);
  const avgValence = d3.mean(data_tmp, (d) => d.valence);

  // Push averages to the array
  averages.push(
    { axis: 'instrumental', value: avgInstrumentalness },
    { axis: 'live', value: avgLiveness },
    { axis: 'valence', value: avgValence },
    { axis: 'danceable', value: avgDanceability },
    { axis: 'energy', value: avgEnergy },
    { axis: 'speech', value: avgSpeechiness },
    { axis: 'acoustic', value: avgAcousticness },  
  );
  const data_radar = [averages];

  // Two divs with equal width
  var svg1 = appendChartDiv(1, 2/5*width,0.6 * height);
  var svg2 = appendChartDiv(2, 2/5*width,0.6 * height);

  // Three divs with equal width
  var svg3 = appendChartDiv(	3, 1/3*width,0.3 * height);
  var svg4 = appendChartDiv(4, 1/3*width,0.3 * height);
  var svg5 = appendChartDiv(5, 1/3*width,0.3 * height);

  // Four divs with widths 1:1:2:2
  var svg6 = appendChartDiv( 6, 1/6*width,0.3 * height);
  var svg7 = appendChartDiv(7, 1/6*width,0.3 * height);
  var svg8 = appendChartDiv( 8, 2/6*width,0.3 * height);
  var svg9 = appendChartDiv( 9, 2/6*width,0.3 * height);
  
  // Call functions to render charts in each div
  RenderDiscript(svg1, data_text,1/2*width*0.98);
  RenderRadarChart(svg2.node(), data_radar, " ","", 300);
  //['popularity', 'loudness', 'tempo']
  RenderHistChart(svg3,data_hist.find(d => d.key === 'popularity').data,'popularity', 'value',1/3*width*0.98,0.3 * height);
  RenderHistChart(svg4,data_hist.find(d => d.key === 'loudness').data,'loudness', 'value',1/3*width*0.98,0.3 * height);
  RenderHistChart(svg5,data_hist.find(d => d.key === 'tempo').data,'tempo', 'value',1/3*width*0.98,0.3 * height);
  
  ARenderBarChart(svg6, data_bar.find(d => d.key === 'explicit').data,'explicit', 'category', 'count',1/6*width*0.98,0.3 * height);
  ARenderBarChart(svg7, data_bar.find(d => d.key === 'mode').data,'mode', 'category', 'count',1/6*width*0.98,0.3 * height);
  ARenderBarChart(svg8, data_bar.find(d => d.key === 'key').data,'key', 'category', 'count',2/6*width*0.98,0.3 * height);
  ARenderBarChart(svg9, data_bar.find(d => d.key === 'time_signature').data,'time_signature', 'category', 'count',2/6*width*0.98,0.3 * height);
}

// Helper function to calculate mode
function getMode(array) {
  var modeMap = {};
  var maxCount = 0;
  var mode;

  array.forEach(function (element) {
    if (!modeMap[element]) modeMap[element] = 1;
    else modeMap[element]++;

    if (modeMap[element] > maxCount) {
      maxCount = modeMap[element];
      mode = element;
    }
  });

  return mode;
}

// Helper function to count unique values and their counts
function countUnique(array) {
  return array.reduce(function (acc, value) {
    acc[value] = (acc[value] || 0) + 1;
    return acc;
  }, {});
}

// Helper function to append a div to the container
function appendChartDiv(id, w,h) {
    var svg_ = svgContainer 
      .append('div')
      .attr('id', id)
      .style('width', w*0.98+'px')
      .style('height', h+ 'px')
      .style('float', 'left')
      //.style('background-color',d3.schemeTableau10[id]); 
  	return svg_
}


//導覽列=====================================================================
// 創建變數引用各個元素
const LRangeDiv = d3.select("#LRangeDiv");
const LInitialDiv = d3.select("#LInitialDiv");
const LGenreDiv = d3.select("#LGenreDiv");
const LFirstLetter = d3.select('#LFirstLetter');
const LRange = d3.select('#LRange');
const LGenre = d3.select('#LGenre');
const ARangeDiv = d3.select("#ARangeDiv");
const AInitialDiv = d3.select("#AInitialDiv");
const AGenreDiv = d3.select("#AGenreDiv");
const ASortDiv = d3.select("#ASortDiv");
const AFirstLetter = d3.select('#AFirstLetter');
const ARange = d3.select('#ARange');
const AGenre = d3.select('#AGenre');
const ASort = d3.select('#ASort');
let initial_letter="a";
let genres_tmp;
// 1. 根據選擇顯示/隱藏相應元素
d3.selectAll('input[name="MainPurpose"]').on('change', function () {
  const selectedValue = d3.select('input[name="MainPurpose"]:checked').property('value');

  // Leaderboard選中時
  if (selectedValue === 'Leaderboard') {
    LRangeDiv.style('display', 'block');
    ARangeDiv.style('display', 'none');
    AInitialDiv.style('display', 'none');
    AGenreDiv.style('display', 'none');
    ASortDiv.style('display', 'none');
    ARange.property('value', 'overview');
    bar_flag = 'all';
    svgContainer.selectAll("*").remove();
    Leaderboard();

  }

  // Analysis選中時
  else if (selectedValue === 'Analysis') {
    LRangeDiv.style('display', 'none');
    LInitialDiv.style('display', 'none');
    LGenreDiv.style('display', 'none');
    ARangeDiv.style('display', 'block');
    ASortDiv.style('display', 'block');
    LRange.property('value', 'all');
    svgContainer.selectAll("*").remove();
    AnalysisAll();
    
  }
});

// 2. LRangeDiv選擇single genre時顯示LInitialDiv和LGenreDiv
LRange.on('change', function () {
  const selectedValue = d3.select(this).property('value');
  bar_flag = selectedValue
  if(selectedValue === 'single genre'){
  	  LInitialDiv.style('display','block');
  		LGenreDiv.style('display','block');
    	svgContainer.selectAll("*").remove();
    	Leaderboard();    	
  }
  else{
  	  LInitialDiv.style('display', 'none');
  		LGenreDiv.style('display', 'none');
    	svgContainer.selectAll("*").remove();
      Leaderboard();
  }

});

// 3. LInitialDiv的options是'a','b','c',...,'z'(英文的26個字母的小寫)
const alphabet = 'abcdefghijklmnopqrstuvwxyz'.split('');
LFirstLetter
  .selectAll('option')
  .data(alphabet)
  .enter()
  .append('option')
  .text(d => d);

// 4. 將LInitialDiv選中的值存到initial_letter

LFirstLetter.on('change', function () {
  initial_letter = d3.select(this).property('value');
  updateGenreDropdown(LGenre, initial_letter);
  svgContainer.selectAll("*").remove();
  Leaderboard();
});

// 5. LRange有改時要重新render
LGenre.on('change', function () {
  bar_gen_flag = d3.select(this).property('value');  
  svgContainer.selectAll("*").remove();
  Leaderboard();
});
  

// 6. ARangeDiv選擇single genre時顯示AInitialDiv和AGenreDiv
ARange.on('change', function () {
  const selectedValue = d3.select(this).property('value')
  if(selectedValue === 'single genre'){
  	  AInitialDiv.style('display','block');
  		AGenreDiv.style('display','block');
      ASortDiv.style('display', 'none');
    	svgContainer.selectAll("*").remove();
    	SingleAnalysis();    	
  }
  else{
  	  AInitialDiv.style('display', 'none');
  		AGenreDiv.style('display', 'none');
      ASortDiv.style('display', 'block');
    	svgContainer.selectAll("*").remove();
      AnalysisAll();
  }
});

ASort.on('change', function () {
  const selectedValue = d3.select(this).property('value')
  if(selectedValue === 'name'){
    ana_flag="G"
       	
  }
  else if (selectedValue === 'pop'){
    ana_flag="P"
  }
  else if (selectedValue === 'shape'){ 
    ana_flag="I"
  }
  svgContainer.selectAll("*").remove();
  AnalysisAll(); 
});

// 7. AInitialDiv的options是'a','b','c',...,'z'(英文的26個字母的小寫)
AFirstLetter
  .selectAll('option')
  .data(alphabet)
  .enter()
  .append('option')
  .text(d => d);


// 8. 將AInitialDiv選中的值存到initial_letter_A
AFirstLetter.on('change', function () {
  initial_letter = d3.select(this).property('value');
  updateGenreDropdown(AGenre, initial_letter);
  svgContainer.selectAll("*").remove();
  SingleAnalysis();
});

// 9. ARange有改時要重新render
AGenre.on('change', function () {
  ana_gen_flag = d3.select(this).property('value');  
  svgContainer.selectAll("*").remove();
  SingleAnalysis();
});

// 10.更新LGenre選單 與 更新 AGenre選單
function updateGenreDropdown(genreDropdown, selectedLetter) {
  genres_tmp = globalGenre.filter(element => element.charAt(0) === selectedLetter);
  genreDropdown.selectAll("option").remove();
  genreDropdown.selectAll("option")
    .data(genres_tmp)
    .enter().append("option")
    .attr("value", d => d)
    .text(d => d);
  bar_gen_flag = genres_tmp[0];
  ana_gen_flag = genres_tmp[0];
}

//讀資料=====================================================================
d3.csv('http://vis.lab.djosix.com:2023/data/spotify_tracks.csv').then(data => {
  data = data.map(function(d) {
    return {
      artists: d.artists,
      album_name: d.album_name,
      track_name: d.track_name,
      track_genre: d.track_genre,
      popularity: +d.popularity,
      explicit: d.explicit === "True" ? 1 : 0,
      acousticness: +d.acousticness,
      danceability: +d.danceability,
      energy: +d.energy,
      instrumentalness: +d.instrumentalness,
      liveness: +d.liveness,
      loudness: +d.loudness,
      speechiness: +d.speechiness,
      valence: +d.valence,
      tempo: +d.tempo,
      mode: +d.mode,
      key: +d.key,
      time_signature: d.time_signature,
      duration_ms: +d.duration_ms
  	};
	});
  console.log(data)
  globalData = data;
  globalGenre = [...new Set(globalData.map(d => d.track_genre))];
  console.log(globalGenre)
  updateGenreDropdown(LGenre, initial_letter);
  updateGenreDropdown(AGenre, initial_letter);
  svgContainer.selectAll("*").remove();
  Leaderboard();
  
});