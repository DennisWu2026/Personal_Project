# AI Power 产品工程速成清单

> 目标：3 个晚上达到"了解级"，能接住总监面第二层追问。
> 定位：您不是要去设计 VRM，而是要能以产品工程总监视角谈产品定义、验证策略与测试挑战。

---

## 第一晚：AI 服务器电源架构全景（2-3 小时）

### 1. 供电链路（先建立全局图）

```
服务器 PSU（CRPS, 54V 母线）
  → 中间总线变换器 IBC（54V → 12V）
    → 多相 Buck VRM（12V → 0.6~1.1V, 300A~1000A+）
      → GPU/CPU/ASIC 核心电压（VDDCR）
```

- AI 加速卡单卡功耗 700W→1500W+，核心电压 <1V，电流达数百安培 → 这就是"功率密度比消费 PMIC 高一个量级"的含义
- 趋势关键词：**48V/54V 直供、垂直供电（SVP/vertical power delivery）、TLVR 拓扑、OAM/UBB 标准卡**

### 2. 必背术语表（面试出现的词，一个都不能卡）

| 术语 | 一句话定义 |
|---|---|
| VRM / VRD | 电压调节器模组/装置，CPU/GPU 核心供电的多相 Buck 系统 |
| SVID | Intel 串行电压识别协议（VR13.HC 等平台，PMBus/SVC+SVD 线） |
| SVI3 | AMD 第三代串行电压接口（Rev 2.0），GPU/CPU 供电主流协议 |
| AVSBus | Intel 服务器侧电压调节通信总线 |
| PMBus | 电源管理标准总线（遥测、配置、故障上报，速率 1MHz+） |
| DrMOS / Intelli-Phase / SPS | 集成驱动+上下管的功率级器件（60A/70A/90A/120A 等级） |
| TLVR | 环形电感耦合的快速瞬态拓扑，AI 加速卡主流 |
| Loadline / Droop / AVP | 输出电压随电流的静态/动态压降控制（阻抗定义，mΩ 口径） |
| 均流（Current Balance） | 各相电流偏差控制，典型要求 ±x% 相间失衡 |
| PSI / PS0-PS3 | 电源状态指示，轻载切相降损耗（phase shedding） |
| OCP/OVP/UVP/OTP | 逐相/总流过流、过压、欠压、过温保护及精度要求 |
| di/dt | 负载瞬态斜率，AI 负载瞬变 0→数百 A/μs 级 |
| VR Ready / 平台认证 | Intel/AMD 对 VRM 设计的官方认证测试流程 |

### 3. 平台协议格局（面试官最可能展开的点）

- **Intel 阵营**：VR13.HC / SVID / AVSBus（参考 MPS MP2965）
- **AMD 阵营**：SVI3 Rev 2.0（参考 Infineon XDPE192C3D、立锜 RT3674AJ）——GPU 供电事实主流
- 关键认知：**VRM 是跟着客户平台走的定制件**——协议兼容与认证通过是产品定义第一约束，这正是"产品工程"与"纯芯片"的差异

---

## 第二晚：VRM Datasheet 精读清单（2-3 小时）

> 阅读顺序：先 MPS 入门文章建立框架 → 再读 2 份 SVI3 控制器 datasheet → 最后扫 DrMOS。

### 0. 入门必读（1 小时）

- **MPS 技术文章：Designing a Multi-Phase Buck Converter with Digital Controllers**
  https://www.monolithicpower.com/designing-a-multi-phase-buck-converter-with-digital-controllers
  （多相系统的工程综述，7 相设计实例，最适合第一篇）

### 1. 多相控制器（核心，选 2 份精读）

| 器件 | 为什么读 | 链接 |
|---|---|---|
| **Infineon XDPE192C3D**（12 相，SVI3 Rev 2.0） | 服务器 GPU 供电旗舰，SVI3 + PMBus 全特性，英文直读 PDF | https://www.infineon.cn/assets/row/public/documents/24/49/infineon-xdpe192c3d-0000-datasheet-en.pdf |
| **立锜 RT3674AJ**（4+1+1 相，SVI3，G-NAVP 拓扑） | 中文厂视角，三轨 CPU/GPU 核心，直接 PDF 可下 | https://www.richtek.com/assets/product_file/RT3674AJ/RT3674AJ_DS-00.pdf |
| **TI TPS53685**（N+M≤8 相，SVI3，TLVR 原生支持） | 看 TLVR 特性与 D-CAP+ 控制的写法 | https://www.ti.com/document-viewer/tps53685/datasheet |
| **MPS MP2965**（7 相，Intel VR13.HC/AVSBus） | Intel 阵营对照，产品页含完整资料包 | https://www.monolithicpower.com/en/mp2965.html |

**精读时只抓 5 件事**：① 相数配置与均流精度 ② Loadline/AVP 的 mΩ 定义 ③ PSI/切相逻辑 ④ 保护精度（OCP 逐相阈值、OTP 响应）⑤ 遥测/故障上报（PMBus/SVI3 寄存器）——其余章节跳过。

### 2. 功率级（扫读 30 分钟）

- MPS **MP86945A**（Intelli-Phase 60A，上述文章配套）——看效率曲线、热阻、电流检测（IMON）
- 同类延伸（知道名字即可）：Renesas ISL69269（Intel SVID 阵营）、onsemi NCP81278 系列、Infineon TDA21572（DrMOS）

---

## 第三晚：转化成岗位语言（面试话术，2 小时）

### 1. "产品工程差异 + 三个挑战"（背熟，对应面试第 5 题）

- **差异**：消费 PMIC 面向通用应用；AI Power 是**平台绑定**产品——协议（SVI3/SVID）、认证（VR Ready）、瞬态（数百 A/μs）、热（1000W 级）都由客户平台定义
- **挑战一：大电流与瞬态**——0.6V/数百 A 下 mΩ 级阻抗控制，di/dt 陡增 → 烧片风险与 guardband 收窄（连接您车规 bump 球经验）
- **挑战二：协议与认证耦合**——测试项直接来自平台规范（loadline 校准、PSI、OCP 精度、效率），不是厂内自定义
- **挑战三：功率密度与热**——DrMOS/TLVR/垂直供电演进快，DUT 设计与热测试成为量产瓶颈

### 2. "立项第一步"（背熟）

> 第一步不是读规格书选平台，是**搞清楚客户平台**：目标 GPU/CPU 的供电规格（SVI3 rail 配置、电流等级、认证要求）→ 应用场景（OAM 卡/UBB/定制板）→ 竞品方案 → 由此反推验证测试策略与量产风险，ATE 选型是后面的执行动作。

### 3. 用测试背景打差异化（您的主场）

- 单相 PMIC 测试 → 多相系统测试的增量：**相间均流精度、瞬态负载板设计、协议层验证（SVI3/PMBus 寄存器级，解决'无法写入回读'老问题）、效率/热的量产口径、correlation 与平台认证对齐**
- 车规经验平移：AEC-Q 思维对 AI 数据中心 24/7 高 Tj 场景的寿命/derating 管理是同一套方法论

### 4. 快速自测（能开口即达标）

1. SVI3 和 SVID 分别是谁家的？VRM 为什么必须跟平台走？
2. Loadline 0.5mΩ 意味着什么？空载 1.0V、满载 200A 时输出电压是多少？（答：0.5mΩ×200A=100mV 压降 → 0.9V。追问：为什么 AI 平台必须用 mΩ 级 loadline 而不是恒压？——瞬态时让电压随电流受控下垂，避免 overshoot 损坏 CPU/GPU）
3. PSI 状态切相解决什么问题？测试上要验证什么？
4. DrMOS 相比分立方案的验证测试差异？
5. 您会怎么设计 300A VRM 的量产 ATE 测试链路（CP/FT/系统级各测什么）？

---

## 时效提示

- 本清单链接均经核实（2026-10）；SVI3 Rev 2.0 与 TLVR 是当前 AI 卡主流，面试提及即加分
- 深入方向（有余力）：NVIDIA OAM/UBB 供电规格、CRPS 标准、Intel VR13.HC 白皮书
