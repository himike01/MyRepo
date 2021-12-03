package trebelz.jvav.instruction.stack;


import trebelz.jvav.instruction.base.NoOperandsInstruction;
import trebelz.jvav.rtda.JVMFrame;

/**
 * @author treblez
 * 交换栈顶两个变量
 */
public class Swap {

    public class SWAP extends NoOperandsInstruction{
        @Override
        public void execute(JVMFrame frame) {
            var stack = frame.getOperandStack();
            var slot1 = stack.popSlot();
            var slot2 = stack.popSlot();
            stack.pushSlot(slot1);
            stack.pushSlot(slot2);
        }
    }

}
