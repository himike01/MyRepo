package trebelz.jvav.instruction.base;

import trebelz.jvav.rtda.JVMFrame;

/**
 * 指令接口，指令共150条，在文件中依次实现
 * @author treblez
 */
public interface Instruction {
    /**
     * 从字节码中提取操作数
     * @param reader
     *
     */
    void fetchOperands(BytecodeReader reader);

    /**
     * 执行指令逻辑
     * @param frame
     */
    void execute(JVMFrame frame);

}
