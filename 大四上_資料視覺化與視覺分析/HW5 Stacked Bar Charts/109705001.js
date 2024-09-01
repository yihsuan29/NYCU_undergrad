(function () {
  'use strict';

  var margin = {top: 10, right: 100, bottom: 250, left: 50},
      width = window.innerWidth*0.8 -margin.left - margin.right,
      height = window.innerHeight -margin.top - margin.bottom;

  var svg = d3.select("#svg")
    .append("svg")
      .attr("width", window.innerWidth*0.8)
      .attr("height", window.innerHeight)
    .append("g")
      .attr("transform",
            "translate(" + margin.left + "," + margin.top + ")");
  var button  = d3.select("#ButtonMenu");
  var legend  = d3.select("#LegendMenu");

  var headInput = d3.select("#head");
  var tailInput = d3.select("#tail");
  var highlightedX;

  //各項指標權重
  const weights = {
    tea: 0.295,
    rea: 0.29,
    cit:0.30,
    ind:0.04,
    int:0.075
  };
  var subgroups=['tea_mod', 'rea_mod', 'cit_mod', 'ind_mod', 'int_mod'];
  const color = (d) =>{
      switch(d){
        case 'tea_mod': return '#9cc9ff';
        case 'rea_mod': return '#fffd9c';
        case 'cit_mod': return '#db9cff';
        case 'ind_mod': return '#9af5a2';
        case 'int_mod': return '#ff9cb5';
      }  };
  var head = 1;
  var tail = 20;
  var sortby = 'all';
  var dir= "descend";

  const render = (data, head, tail, sortby, dir) =>{
    rearrangeSubgroups(sortby);
    //根據誰來排
    var data_ = data.slice();
    console.log(sortby);
    data_.sort(function(b, a) {
        switch (sortby) {
            case 'all':
                return b.all_rank - a.all_rank;
            case 'tea':
                return b.tea_rank - a.tea_rank;
            case 'rea':
                return b.rea_rank - a.rea_rank;
            case 'cit':
                return b.cit_rank - a.cit_rank;
            case 'ind':
                return b.ind_rank - a.ind_rank;
            case 'int':
                return b.int_rank - a.int_rank;
        }
  	});
    //只顯示head~tail的資料
    data_= data_.slice(head-1, tail);
    data_.sort(function(b, a) {
      if(dir==="descend"){
        switch (sortby) {
            case 'all':
                return b.all_rank - a.all_rank;
            case 'tea':
                return b.tea_rank - a.tea_rank;
            case 'rea':
                return b.rea_rank - a.rea_rank;
            case 'cit':
                return b.cit_rank - a.cit_rank;
            case 'ind':
                return b.ind_rank - a.ind_rank;
            case 'int':
                return b.int_rank - a.int_rank;
        }
      }
      else
      {
        switch (sortby) {
            case 'all':
                return a.all_rank - b.all_rank;
            case 'tea':
                return a.tea_rank - b.tea_rank;
            case 'rea':
                return a.rea_rank - b.rea_rank;
            case 'cit':
                return a.cit_rank - b.cit_rank;
            case 'ind':
                return a.ind_rank - b.ind_rank;
            case 'int':
                return a.int_rank - b.int_rank;
        }
      }
  	});
    //x軸都有誰
    var groups = d3.map(data_, function(d){return(d.name)}).keys();
    
    var x = d3.scaleBand()
        .domain(groups)
        .range([0, width])
        .padding([0.2]);
    
    svg.append("g")
      .attr("transform", "translate(0," + height + ")")
      .call(d3.axisBottom(x).tickSizeOuter(0))
    	.selectAll("text")
        .style("text-anchor", "start")
        .attr("dx", ((tail - head) <= 19 ? 0.5 : 0.8)+"em")
        .attr("dy", ((tail - head) <= 19 ? 0.5 : -0.6)+"em")
        .attr("transform",  "rotate(" + ((tail - head) <= 19 ? 45 : 65) + ")");
    //y軸
    var y = d3.scaleLinear()
      .domain([0, 100])
      .range([ height, 0 ]);
    svg.append("g")
      .call(d3.axisLeft(y));
    
    //data->stacked data
    var stackedData = d3.stack()
      .keys(subgroups)
      (data_);
    console.log(stackedData);
    
    //畫圖
    svg.append("g")
      .selectAll("g")
      .data(stackedData)
      .enter()
      .append("g")
        .attr("fill", (d)=> color(d.key))
        .selectAll("rect")
        .data((d)=>d)
        .enter()
      	.append("rect")
          .attr("x", (d) => x(d.data.name))
          .attr("y", (d) => y(d[1]))
          .attr("width",x.bandwidth())
          .attr("height", (d) => y(d[0]) - y(d[1]))
    			.on("mouseover", function(d) {
      			highlightedX = d.data.name;
            svg.selectAll("rect")
              .filter(function(rectData) {
                return rectData.data.name === highlightedX;
              })
              .style("stroke", "red");
      			
      			showTooltip(d,sortby);})
    			.on("mousemove", function(d) {
            tooltip.style("left", (d3.event.pageX + 10) + "px")
              .style("top", (d3.event.pageY - 30) + "px");
          })
    			.on("mouseout", function(d) {
             highlightedX = null;
            svg.selectAll("rect")
              .style("stroke", "none");
            tooltip.style("opacity", 0);
          });

    //legend---------------------------------------------------------------------------------
    legend.selectAll('*').remove();
    const legendData = [
        { label: 'Teaching(29%)', color: color('tea_mod') },
        { label: 'Research(29.5%)', color: color('rea_mod') },
        { label: 'Citations(30%)', color: color('cit_mod') },
        { label: 'Industry Income(4%)', color: color('ind_mod') },
        { label: 'International(7.5%)', color: color('int_mod') }
      ];

    const legendSvg = legend
      .append('svg')
      .attr('width', 180)
      .attr('height', 120)
      .append('g')
      .attr('transform', 'translate(0, 10)');
    
    const legendItems = legendSvg
      .selectAll('g')
      .data(legendData)
      .enter()
      .append('g')
      .attr('transform', (d, i) => `translate(0, ${i * 20})`);
    
    legendItems
      .append('rect')
      .attr('width', 15)
      .attr('height', 15)
      .style('fill', (d) => d.color);
    
    legendItems
      .append('text')
      .attr('x', 20)
      .attr('y', 10)
      .attr('dy', '0.35em')
      .text((d) => d.label);
    
    //根據Title 的 head tail改變-----------------------------------------------------------------------------------------
  	headInput.on("input", function () {
      if(+(headInput.property("value"))<=tail)
      {
        head = +(headInput.property("value"));
        svg.selectAll('*').remove();
        render(data, head, tail, sortby,dir);
      }
      else {
         headInput.property("value", tail);
      }
    });
  	tailInput.on("input", function () {
      if(+(tailInput.property("value"))>=head)
      {
        tail = +(tailInput.property("value"));
        svg.selectAll('*').remove();
        render(data, head, tail, sortby,dir);
      }
      else {
        tailInput.property("value", head);
      }
    });
    //根據button 改變sorting----------------------------------------------------------------------------
    d3.selectAll('input[name="sort"]').on("change", function() {
      sortby = this.value;
      svg.selectAll('*').remove();
      render(data, head, tail, sortby,dir);
    });
    d3.selectAll('input[name="dir"]').on("change", function() {
      dir = this.value;
      svg.selectAll('*').remove();
      render(data, head, tail, sortby,dir);
    });
    
  };

  d3.csv('http://vis.lab.djosix.com:2023/data/TIMES_WorldUniversityRankings_2024.csv').then(data => {
    //指讀有排名的
    data = data.filter(function(d) {
      return d.rank !== "Reporter";
    });
    //只讀重要的欄位
    data = data.map(function(d) {
      return {
        name: d.name,
        all_rank: +d.scores_overall_rank,
        tea_score: +d.scores_teaching,
        tea_rank: +d.scores_teaching_rank,
        rea_score: +d.scores_research,
        rea_rank: +d.scores_research_rank,
        cit_score: +d.scores_citations,
        cit_rank: +d.scores_citations_rank,
        ind_score: +d.scores_industry_income,
        ind_rank: +d.scores_industry_income_rank,
        int_score: +d.scores_international_outlook,
        int_rank: +d.scores_international_outlook_rank
      };
    });
    //重新計算overall_score(因為後面的是區間)
    data = data.map(function(d) {
      d.tea_mod = +(d.tea_score * weights.tea).toFixed(4),
      d.rea_mod = +(d.rea_score * weights.rea).toFixed(4),
      d.cit_mod= +(d.cit_score * weights.cit).toFixed(4),
      d.ind_mod = +(d.ind_score * weights.ind).toFixed(4),
      d.int_mod = +(d.int_score * weights.int).toFixed(4),
      d.all_score = +(d.tea_mod + d.rea_mod + d.cit_mod + d.ind_mod + d.int_mod).toFixed(1);
      return d;
    }); 
    console.log(data);
    data = data.sort((a,b)=>b.all_score-a.all_score);
  	data.forEach((item,index) => {
    	item.all_rank = index+1;
    });
    render(data, head, tail, sortby,dir);
  });

  function rearrangeSubgroups(sortby) {
    subgroups = ['tea_mod', 'rea_mod', 'cit_mod', 'ind_mod', 'int_mod'];
    switch (sortby) {
      case 'tea':
        subgroups = ['tea_mod'].concat(subgroups.filter(subgroup => subgroup !== 'tea_mod'));
        break;
      case 'rea':
        
        subgroups = ['rea_mod'].concat(subgroups.filter(subgroup => subgroup !== 'rea_mod'));
        break;
      case 'cit':
        subgroups = ['cit_mod'].concat(subgroups.filter(subgroup => subgroup !== 'cit_mod'));
        break;
      case 'ind':
        subgroups = ['ind_mod'].concat(subgroups.filter(subgroup => subgroup !== 'ind_mod'));
        break;
      case 'int':
        subgroups = ['int_mod'].concat(subgroups.filter(subgroup => subgroup !== 'int_mod'));
        break;
      default:
        subgroups = ['tea_mod', 'rea_mod', 'cit_mod', 'ind_mod', 'int_mod'];
    }
  }
  var tooltip = d3.select("body").append("div")
    .attr("class", "tooltip")
    .style("opacity", 0);

  function showTooltip(d, sortby) {
    const name = d.data.name;

    tooltip.html(`
    <text>Name:  ${d.data.name}</text><br><br>
    <text>Total Rank: ${d.data.all_rank}</text> <br>
    <text>Total Score: ${d.data.all_score}</text> <br><br>
    <text>Selected Rank: ${d.data[sortby + "_rank"]}</text> <br>
    <text>Selected Score: ${d.data[sortby + "_score"]}</text> <br><br>
    <text>Teaching Score: ${d.data.tea_score}</text> <br>
    <text>Research Score: ${d.data.rea_score}</text> <br>
    <text>Citation Score: ${d.data.cit_score}</text> <br>
    <text>Industry Score: ${d.data.ind_score}</text> <br>
    <text>International Score: ${d.data.int_score}</text> <br>
  `);
    tooltip.style("opacity", 1);
  }

}());
