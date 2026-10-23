---
name: "ate-code-optimize"
description: "Optimizes ATE test program C++ code (V93K SmarTest, UltraFLEX, etc.) while strictly preserving test behavior, execution order, timing, and measurement accuracy. Invoke when user asks to optimize, simplify, speed up, or clean up ATE test program code, reduce test time, refactor test methods, or eliminate duplication in test suites."
---

# ATE Code Optimize

Optimize and simplify ATE test program C++ code through a three-phase process: **simplify → optimize → review & verify**. Adapted from industry best practices (code-polish / code-simplifier / qt-cpp-review patterns) and specialized for ATE test program constraints.

Resolve scope once. Make only high-confidence changes. Report with risk classification.

## 铁律：不可变项（Invariants）

ATE programs are timing- and hardware-sensitive. Before ANY change, identify and record these invariants. A change that violates any invariant is **forbidden by default**:

1. **测试结果不变**: pass/fail 判定、binning 分类结果、测量值的数值与单位。
2. **执行顺序不变**: test item 执行顺序、test suite 调用顺序、binning 依赖关系。
3. **时序不变**: 仪器 setup/teardown 顺序、settling time、采样数、量程(range)/分辨率/resolution 设置、trigger 位置。
4. **测量精度不变**: 校准(calibration)、补偿(compensation/offset)、 liners/GDIB 前后处理逻辑。
5. **公共契约不变**: test method 的参数签名、参数名、test table 列结构、输出文件格式(STDF/自定义)。
6. **失败路径不变**: 仪器错误处理、超时(timeout)、abort/重试逻辑。

如无法确认某项是否属于以上不变式，**停止并询问**，不要猜测。

## Phase 0: 范围界定（Scope Resolution）

1. 要求明确的范围：文件、目录、test suite 名、或"本次修改的代码"。
2. 排除：生成的输出文件、导入的工具库、第三方 ATE 平台头文件(如 V93K 的 `VCAP.hpp`、UltraFLEX 的 `ultraflex.h` 等平台自带文件)。
3. 记录一个权威范围集合，后续不再扩大或重新计算。范围为空则停止。
4. 大范围（>2500 行）分片处理，逐片报告，避免上下文过载。

## Phase 1: 简化（Simplify）

只做高置信度简化。**无操作(no-op)是合法结果**——比错误的简化好。

应该做:
- 扁平化可避免的控制流嵌套（深嵌套的 if/else 与循环）。
- 消除真实的重复代码：多处重复的仪器 setup 序列、重复的参数读取模式、复制粘贴的测试项目模板——仅当抽象后总复杂度降低时。
- 删除真实死代码：本次会话编辑产生的未用变量、不可达分支、注释掉的旧测试代码。
- 收紧局部类型与常量命名（如魔数提取为具名常量，注明单位与来源）。
- 澄清误导性命名：如 `result1`/`tmp` → 具体测量含义（`leakage_current_uv`）。

禁止做:
- 按行数拆分文件或函数（行数不是复杂度指标）。
- 架构级清理：改变 test method 继承结构、重排 test class 层级、改变 test table 组织。
- 合并"看起来相似"的不同测试的 setup/teardown——时序差异可能是有意的。
- 将同步仪器调用改为异步/并行，除非用户明确要求并理解 multisite/parallel test 的影响。
- 添加投机性配置项（"以后可能用到"的参数）。
- 用一次性抽象替换可读的重复（三行相似代码好过一个错误的抽象）。
- 改动任何 settling time、等待循环的延时数值、采样点数。

## Phase 2: ATE 特定优化（Optimize）

在简化后的代码上，按以下维度寻找优化机会。每项发现必须给出**预期收益**（测试时间、资源占用、维护性）与**风险评级**。

### 测试时间（Test Time Reduction — ATE 核心指标）
- 循环内不变的仪器命令/setup 外提到循环外（如重复的量程设置、重复的 `connect`/`disconnect`）。
- 重复的仪器状态查询合并（如同一循环内多次 `get_status`）。
- 无依赖的测量是否可通过平台原生机制并行化——**仅报告建议**，不擅自实现。
- 死等待：固定延时 `sleep` 是否可改为状态轮询——**仅报告建议**，等待数值本身不改。
- 数据记录：高频 `printf`/日志写盘是否可降频或条件化（保持调试能力）。

### 资源占用
- 重复 open/close 的仪器会话/文件句柄复用。
- 测试间未释放的缓冲区、数组。

### C++ 正确性（引用 qt-cpp-review 六维度的 ATE 适配）
- 内存：裸 new/delete 的所有权明确化（ATE 框架对象生命周期常由平台管理，勿用智能指针强接管平台对象）。
- 数值：浮点比较用容差而非 `==`；测量值单位混用（V/mV/uV）检查。
- 边界：循环边界、数组索引、除零保护。
- 并发：若涉及 multisite 线程，检查共享仪器状态的访问保护——只报告，不改并发结构。

## Phase 3: 审查与验证（Review & Verify）

### 风险分级
对每处修改按此分级，**MEDIUM 以上需在报告中醒目标注**:

- **CRITICAL**: 可能改变测试结果、执行顺序、时序、精度——默认禁止，除非用户明确批准。
- **HIGH**: 可能影响测量裕量(margin)、测试时间劣化、或错误路径行为。
- **MEDIUM**: 资源泄漏、复杂度热点、测试覆盖缺口、弱验证准则。
- **LOW**: 局部清晰度、命名、注释改进。

### 验证（按可行范围执行）
1. **编译**: 目标平台工具链编译通过（V93K/Sm93000 等平台编译命令按项目配置）。
2. **行为比对**: 提示用户用相同 pattern/lot 数据比对优化前后的 bin 分布与测量值。无法运行时，明确说明"未验证"并列出残余风险。
3. **静态检查**: 只读工具（grep/read）确认无遗漏的符号引用、头文件依赖。

### 报告格式
报告以 `### ⨳ ATE code optimize — 结果` 开头，包含：
- **范围**: 文件数与根路径/glob，不逐一枚举文件。
- **不变式确认**: 逐项声明六个铁律已检查且未违反。
- **修改清单**: 每项含 位置(file:line)、类型(简化/时间优化/正确性)、风险级别、证据、预期收益。
- **建议未实施项**: 需要用户决策的项（如并行化、死等待改轮询），含影响分析。
- **验证**: 已执行的验证命令与结果；跳过的验证及原因。
- **残余风险**: 假设、假设错误的后果、如何检查。

审查未发现问题时，声明 `✅ No verified findings.`。被不变式冲突阻止时，声明 `⛔ blocked` 并给出所需的用户决策。

## 与 ate-program-review 的配合

本技能负责**修改代码**（优化/简化）；本地 `ate-program-review` 技能负责**只读审查**（规范符合性、常见陷阱）。推荐流程：优化完成后，调用 ate-program-review 做发布前审查。

## 来源参考

本技能设计整合自以下公开技能的模式：
- PaulRBerg/agent-skills `code-polish`（行为保持 + 风险分级 + no-op 合法）
- anthropics/claude-plugins-official `code-simplifier`（清晰优于简洁 + 反过度简化）
- TheQtCompanyRnD/agent-skills `qt-cpp-review`（分片控制 + 六维度 C++ 分析 + 只报告高置信度问题）
