(function () {
  'use strict';

  var margin = {
      top: 20,
      right: 30,
      bottom: 0,
      left: 100,
    },
    width =
      window.innerWidth -
      margin.left -
      margin.right,
    height =
      window.innerHeight -
      margin.top -
      margin.bottom;

  var svg = d3
    .select('#svg')
    .append('svg')
    .attr(
      'width',
      width * 0.7 + margin.left + margin.right
    )
    .attr(
      'height',
      height + margin.top + margin.bottom
    )
    .append('g')
    .attr(
      'transform',
      'translate(' +
        margin.left +
        ',' +
        margin.top +
        ')'
    );

  var keys = [
    'house2',
    'house3',
    'house4',
    'house5',
    'unit1',
    'unit2',
    'unit3',
  ];
  const color_keys = [
    'house2',
    'house3',
    'house4',
    'house5',
    'unit1',
    'unit2',
    'unit3',
  ];

  const color = d3
    .scaleOrdinal()
    .domain(color_keys)
    .range(d3.schemeTableau10);

  const legendWidth =
    width * 0.2 + margin.left + margin.right;
  const legendHeight =
    height + margin.top + margin.bottom + 10;

  const LgdMenu = d3
    .select('#LegendMenu')
    .append('svg')
    .attr('width', legendWidth)
    .attr('height', legendHeight)
    .append('g')
    .attr(
      'transform',
      'translate(' +
        0 +
        ',' +
        (legendHeight - keys.length * 40) / 2 +
        ')'
    );

  var customTicks = [
    '30/06/2007',
    '30/06/2008',
    '30/06/2009',
    '30/06/2010',
    '30/06/2011',
    '30/06/2012',
    '30/06/2013',
    '30/06/2014',
    '30/06/2015',
    '30/06/2016',
    '30/06/2017',
    '30/06/2018',
    '30/06/2019',
  ];

  var timeParser = d3.timeParse('%d/%m/%Y');
  var timeFormat = d3.timeFormat('%Y/%m/%d');

  const render = (data) => {
    var x = d3
      .scaleLinear()
      .domain(d3.extent(data, (d) => d.saledate))
      .range([0, width * 0.7]);

    svg
      .append('g')
      .attr(
        'transform',
        'translate(0,' + margin.top * 2 + ')'
      )
      .call(
        d3
          .axisBottom(x)
          .tickValues(
            customTicks.map(function (d) {
              return timeParser(d);
            })
          )
          .tickFormat(timeFormat)
          .tickSize(height * 0.8 - 80)
      )
      .select('.domain')
      .remove();

    svg
      .selectAll('.tick line')
      .attr('stroke', '#b8b8b8');

    var y = d3
      .scaleLinear()
      .domain([-4500000, 4500000])
      .range([0, height - 80]);

    var stackedData = d3
      .stack()
      .offset(d3.stackOffsetSilhouette)
      .keys(keys)(data);
    
  	//themeriver====================================================================
    var area = d3
      .area()
      .x(function (d) {
        return x(d.data.saledate);
      })
      .y0(function (d) {
        return y(d[0]);
      })
      .y1(function (d) {
        return y(d[1]);
      })
      .curve(d3.curveBasis);

    svg
      .selectAll('.river')
      .data(stackedData)
      .enter()
      .append('path')
      .attr('class', 'river')
      .attr('d', (d) => area(d))
      .style('fill', (d) => color(d.key));

    //hover interaction
    var scatterData = [
      ['saledate', 'key', 'value', 'y0', 'y1'],
    ];
    for (let i = 0; i < stackedData.length; i++) {
      var key = stackedData[i].key;
      for (
        let j = 0;
        j < stackedData[i].length;
        j++
      ) {
        var saledate =
          stackedData[i][j].data.saledate;
        var value = stackedData[i][j].data[key];
        var y0 = stackedData[i][j][0];
        var y1 = stackedData[i][j][1];
        scatterData.push([
          saledate,
          key,
          value,
          y0,
          y1,
        ]);
      }
    }
    //the hover target=================================================================
    svg
      .selectAll('.rectangles')
      .data(scatterData.slice(1))
      .enter()
      .append('rect')
      .attr('x', (d) => x(d[0]) - 5)
      .attr('y', (d) => y(d[3]))
      .attr('width', 10)
      .attr('height', (d) => y(d[4]) - y(d[3]))
      .attr('fill', 'transparent')
      .on('mouseenter', function (d) {
        var circleRadius = 4;
        var cx = x(d[0]) - circleRadius;
        var cy = y(d[3]) - circleRadius;
      
        //the point
        svg
          .append('circle')
          .attr('cx', cx)
          .attr('cy', cy + 3)
          .attr('r', circleRadius)
          .attr('fill', color(d[1]))
          .attr('class', 'tooltip-circle')
          .attr('stroke', 'white');

        var rectWidth = 150;
        var rectHeight = 100;
        var rectX = Math.max(
          -50,
          Math.min(
            cx - rectWidth / 2,
            width * 0.7 - rectWidth
          )
        );
        var rectY = cy - rectHeight - 10;
        var type = d[1].replace(/[0-9]/g, '');
        var bedrooms = d[1].replace(/\D/g, '');
        // tooltip
        svg
          .append('rect')
          .attr('x', rectX)
          .attr('y', rectY)
          .attr('width', rectWidth)
          .attr('height', rectHeight)
          .attr('fill', 'white')
          .attr('stroke', 'black')
          .attr('class', 'tooltip-rect');

        svg
          .append('text')
          .attr('x', rectX + 15)
          .attr('y', cy - rectHeight + 10)
          .attr('text-anchor', 'left')
          .text('Type: ' + type)
          .attr('class', 'tooltip-text');

        svg
          .append('text')
          .attr('x', rectX + 15)
          .attr('y', cy - rectHeight * 0.75 + 10)
          .attr('text-anchor', 'left')
          .text('Bedrooms: ' + bedrooms)
          .attr('class', 'tooltip-text');

        svg
          .append('text')
          .attr('x', rectX + 15)
          .attr('y', cy - rectHeight * 0.5 + 10)
          .attr('text-anchor', 'left')
          .text('Time: ' + timeFormat(d[0]))
          .attr('class', 'tooltip-text');

        svg
          .append('text')
          .attr('x', rectX + 15)
          .attr('y', cy - rectHeight * 0.25 + 10)
          .attr('text-anchor', 'left')
          .text('MA: ' + d[2])
          .attr('class', 'tooltip-text');
      })
      .on('mouseleave', function () {
        svg.select('.tooltip-circle').remove();
        svg.select('.tooltip-rect').remove();
        svg.selectAll('.tooltip-text').remove();
      });

    //Lgd================================================================================
    LgdMenu.append('text').text('Type & # bedroom');
    const Lgdy = d3
      .scalePoint()
      .domain(keys)
      .range([30, keys.length * 28]);

    const LgdG = LgdMenu.selectAll('.domain')
      .data(keys)
      .enter()
      .append('g')
      .attr(
        'transform',
        (d) => 'translate(0, ' + Lgdy(d) + ')'
      );

    LgdG.append('rect')
      .attr('width', 20)
      .attr('height', 5)
      .attr('y', -7)
      .attr('fill', (d) => color(d));

    LgdG.append('text')
      .text((d) => d)
      .attr('x', 30)
      .attr('class', 'label')
      .attr('fill', 'black');

    var LgdyId = {};
    const LgdyScale = (d) =>
      LgdyId[d] == null ? Lgdy(d) : LgdyId[d];

    const drag = (d) => {
      LgdyId[d] = Math.min(
        keys.length * 28 + 14,
        Math.max(20, d3.event.y)
      );

      keys.sort(
        (p, q) => LgdyScale(p) - LgdyScale(q)
      );

      Lgdy.domain(keys);
      LgdG.attr(
        'transform',
        (d) => 'translate(0,' + LgdyScale(d) + ')'
      );
    };

    const transition = (g) =>
      g.transition().duration(300);

    const dragend = (d) => {
      delete LgdyId[d];
      transition(LgdG).attr(
        'transform',
        (p) => 'translate(0,' + Lgdy(p) + ')'
      );
      console.log(keys);
      svg.selectAll('*').remove();
      LgdMenu.selectAll('*').remove();
      render(data);
    };

    LgdG.call(
      d3
        .drag()
        .subject({ y: Lgdy })
        .on('drag', drag)
        .on('end', dragend)
    );
    //txt==============================================================================
    svg
      .append('text')
      .attr('x', 50)
      .attr('y', height * 0.8)
      .attr('text-anchor', 'left')
      .text('Interaction Hint:')
      .attr('class', 'interaction-hint');

    svg
      .append('text')
      .attr('x', 50)
      .attr('y', height * 0.8 + 30)
      .attr('text-anchor', 'left')
      .text('Hover the graph to see the detail')
      .attr('class', 'interaction-hint');

    svg
      .append('text')
      .attr('x', 50)
      .attr('y', height * 0.8 + 60)
      .attr('text-anchor', 'left')
      .text('Drag the legend to reorder the stream')
      .attr('class', 'interaction-hint');
  };

  d3.csv('http://vis.lab.djosix.com:2023/data/ma_lga_12345.csv').then(function (data) {
    //從 date, MA, type, room
    //變 date, house2_MA, house3_MA, house4_MA, house5_MA, unit1_MA, unit2_MA,unit3_MA

    var classes = [
      ['house', '2'],
      ['house', '3'],
      ['house', '4'],
      ['house', '5'],
      ['unit', '1'],
      ['unit', '2'],
      ['unit', '3'],
    ];

    var uniq_date = Array.from(
      new Set(data.map((d) => d.saledate))
    );

    var data_ = [];

    uniq_date.forEach(function (saledate) {
      var entry = { saledate: saledate };

      classes.forEach(function (classInfo) {
        var type = classInfo[0];
        var bedrooms = classInfo[1];

        var filtered = data.filter(function (d) {
          return (
            d.type === type &&
            d.bedrooms == bedrooms &&
            d.saledate === saledate
          );
        });

        if (filtered.length > 0) {
          entry[type + bedrooms] = +filtered[0].MA;
        } else {
          entry[type + bedrooms] = 0;
        }
      });

      data_.push(entry);
    });

    data_.forEach(function (d) {
      d.saledate = timeParser(d.saledate);
    });

    data_.sort(function (a, b) {
      return d3.ascending(a.saledate, b.saledate);
    });
    render(data_);
  });

}());

