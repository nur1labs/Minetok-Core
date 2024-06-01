<!-- Styles -->
<style>
#chartdiv {
  width: 100%;
  height: 500px;
}
</style>

<!-- Resources -->
<script src="https://cdn.amcharts.com/lib/4/core.js"></script>
<script src="https://cdn.amcharts.com/lib/4/charts.js"></script>
<script src="https://cdn.amcharts.com/lib/4/themes/animated.js"></script>
<script>
    window.setInterval('refresh()', 100000); 	
    // Call a function every 10000 milliseconds 
    // (OR 10 seconds).

    // Refresh or reload page.
    function refresh() {
        window .location.reload();
    }
</script>

<!-- Chart code -->
<script>
am4core.ready(function() {

// Themes begin
am4core.useTheme(am4themes_animated);
// Themes end

var chart = am4core.create("chartdiv", am4charts.XYChart);
chart.paddingRight = 20;

chart.dateFormatter.inputDateFormat = "yyyy-MM-dd";

var dateAxis = chart.xAxes.push(new am4charts.DateAxis());
dateAxis.renderer.grid.template.location = 0;

var valueAxis = chart.yAxes.push(new am4charts.ValueAxis());
valueAxis.tooltip.disabled = true;

var series = chart.series.push(new am4charts.CandlestickSeries());
series.dataFields.dateX = "date";
series.dataFields.valueY = "close";
series.dataFields.openValueY = "open";
series.dataFields.lowValueY = "low";
series.dataFields.highValueY = "high";
series.simplifiedProcessing = true;
series.tooltipText = "Open:{openValueY.value} xau\nLow:{lowValueY.value} xau\nHigh:{highValueY.value} xau\nClose:{valueY.value} xau";

chart.cursor = new am4charts.XYCursor();

// a separate series for scrollbar
var lineSeries = chart.series.push(new am4charts.LineSeries());
lineSeries.dataFields.dateX = "date";
lineSeries.dataFields.valueY = "close";
// need to set on default state, as initially series is "show"
lineSeries.defaultState.properties.visible = false;

// hide from legend too (in case there is one)
lineSeries.hiddenInLegend = true;
lineSeries.fillOpacity = 0.5;
lineSeries.strokeOpacity = 0.5;

var scrollbarX = new am4charts.XYChartScrollbar();
scrollbarX.series.push(lineSeries);
chart.scrollbarX = scrollbarX;

chart.data = [ {
    "date": "2021-05-18",
    "open": "5400.25",
    "high": "9510.96",
    "low": "3400.77",
    "close": "4908.55"
  }, {
    "date": "2021-05-19",
    "open": "4908.55",
    "high": "10981.33",
    "low": "2223.77",
    "close": "7532.88"
  }, {
    "date": "2021-05-20",
    "open": "7532.55",
    "high": "10981.33",
    "low": "2223.77",
    "close": "6803.78"
  }, {
    "date": "2021-05-21",
    "open": "6803.55",
    "high": "10981.33",
    "low": "5045.33",
    "close": "7033.33"
  }, {
    "date": "2021-05-22",
    "open": "7033.33",
    "high": "10981.33",
    "low": "6055.33",
    "close": "7609.33"
  }, {
    "date": "2021-05-23",
    "open": "7609.33",
    "high": "10981.33",
    "low": "6055.33",
    "close": "7609.33"
  }, {
    "date": "2021-05-24",
    "open": "7609.33",
    "high": "10981.33",
    "low": "6055.33",
    "close": "7609.33"
  }, {
    "date": "2021-05-25",
    "open": "7609.33",
    "high": "10981.33",
    "low": "6055.33",
    "close": "7674.55"
  }, {
    "date": "2021-05-26",
    "open": "7674.55",
    "high": "10981.33",
    "low": "6055.33",
    "close": "10105.31"
  }, {
    "date": "2021-05-27",
    "open": "10105.55",
    "high": "10205.27",
    "low": "6055.33",
    "close": "8003.11"
  }, {
    "date": "2021-05-28",
    "open": "8003.11",
    "high": "10205.27",
    "low": "6055.33",
    "close": "8003.11"
  }, {
    "date": "2021-05-29",
    "open": "8003.11",
    "high": "10205.27",
    "low": "6055.33",
    "close": "8003.11"
  }, {
    "date": "2021-05-30",
    "open": "8003.11",
    "high": "15454.11",
    "low": "7341.33",
    "close": "14574.11"
  }, {
    "date": "2021-05-31",
    "open": "14574.11",
    "high": "16303.11",
    "low": "10321.11",
    "close": "14574.11"
  }, {
    "date": "2021-06-1",
    "open": "14574.11",
    "high": "16303.11",
    "low": "11441.31",
    "close": "14574.11"
  }, {
    "date": "2021-06-2",
    "open": "14574.11",
    "high": "16303.11",
    "low": "9082.63",
    "close": "14574.11"
  }, {
    "date": "2021-06-3",
    "open": "14574.11",
    "high": "16303.11",
    "low": "12434.77",
    "close": "14574.11"
  }];

}); // end am4core.ready()
</script>

<!-- HTML -->
<p>this exchange is API from nur1labs.my/project. or exchange.kwn.my. please provide local to take it as
stable daily mark off. Due To Delay on Sell we maintenance by time 22-31th may. API wil stopping update and slow.
</br></br>
Jo Yap</p>
<div id="chartdiv"></div>
