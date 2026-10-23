(function() {
  var style = getComputedStyle(document.documentElement);
  var accent = style.getPropertyValue('--accent').trim();
  var accent2 = style.getPropertyValue('--accent2').trim();
  var ink = style.getPropertyValue('--ink').trim();
  var muted = style.getPropertyValue('--muted').trim();
  var rule = style.getPropertyValue('--rule').trim();
  var bg2 = style.getPropertyValue('--bg2').trim();

  // ===== 图 1: delay 参数分布 =====
  var chartDelay = echarts.init(document.getElementById('chart-delay'), null, { renderer: 'svg' });
  chartDelay.setOption({
    animation: false,
    tooltip: { trigger: 'axis', appendToBody: true },
    legend: { data: ['delay_ms (次数)', 'delay_us (次数)'], top: 0, textStyle: { color: muted } },
    grid: { left: 50, right: 20, top: 40, bottom: 45 },
    xAxis: {
      type: 'category',
      data: ['1', '2', '3', '4', '5', '7', '10', '15', '20', '30', '50', '100', '100', '200', '500', '1000', '2000', '3000'],
      name: '数值',
      nameLocation: 'middle',
      nameGap: 30,
      axisLabel: { color: muted, interval: 0, rotate: 45 },
      axisLine: { lineStyle: { color: rule } },
      splitLine: { show: false }
    },
    yAxis: {
      type: 'log',
      name: '出现次数 (对数轴)',
      axisLabel: { color: muted, formatter: '{value}' },
      axisLine: { lineStyle: { color: rule } },
      splitLine: { lineStyle: { color: rule, type: 'dashed' } }
    },
    series: [
      {
        name: 'delay_ms (次数)',
        type: 'bar',
        itemStyle: { color: accent },
        data: [317, 84, 11, 1, 19, 1, 10, 3, 4, 5, 1, 7, 0, 0, 0, 0, 0, 0]
      },
      {
        name: 'delay_us (次数)',
        type: 'bar',
        itemStyle: { color: accent2 },
        data: [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 24, 51, 278, 65, 3, 2]
      }
    ]
  });
  window.addEventListener('resize', function() { chartDelay.resize(); });

  // ===== 图 2: 代码构成 =====
  var chartComp = echarts.init(document.getElementById('chart-composition'), null, { renderer: 'svg' });
  chartComp.setOption({
    animation: false,
    tooltip: { trigger: 'item', appendToBody: true, formatter: '{b}<br/>{c} 行 ({d}%)' },
    legend: { bottom: 0, textStyle: { color: muted } },
    series: [{
      type: 'pie',
      radius: ['42%', '68%'],
      center: ['50%', '45%'],
      label: { color: ink, formatter: '{b}\n{c} 行' },
      data: [
        { value: 9767, name: '活跃代码', itemStyle: { color: accent } },
        { value: 1257, name: '注释死代码', itemStyle: { color: accent2 } }
      ]
    }]
  });
  window.addEventListener('resize', function() { chartComp.resize(); });

  // ===== 图 3: 建议项风险分布 =====
  var chartRisk = echarts.init(document.getElementById('chart-risk'), null, { renderer: 'svg' });
  chartRisk.setOption({
    animation: false,
    tooltip: { trigger: 'axis', appendToBody: true },
    grid: { left: 90, right: 30, top: 20, bottom: 35 },
    xAxis: {
      type: 'value',
      minInterval: 1,
      axisLabel: { color: muted },
      axisLine: { lineStyle: { color: rule } },
      splitLine: { lineStyle: { color: rule, type: 'dashed' } }
    },
    yAxis: {
      type: 'category',
      data: ['E · 仅报告(铁律约束)', 'D · 正确性小修', 'C1 · 表驱动重构', 'B · 死代码清理', 'A · 发布遗留'],
      axisLabel: { color: ink },
      axisLine: { lineStyle: { color: rule } }
    },
    series: [{
      type: 'bar',
      barWidth: '55%',
      label: { show: true, position: 'right', color: ink },
      data: [
        { value: 4, itemStyle: { color: '#6b7690' } },
        { value: 2, itemStyle: { color: '#2e7d43' } },
        { value: 1, itemStyle: { color: '#b07818' } },
        { value: 2, itemStyle: { color: '#2e7d43' } },
        { value: 2, itemStyle: { color: accent2 } }
      ]
    }]
  });
  window.addEventListener('resize', function() { chartRisk.resize(); });
})();
