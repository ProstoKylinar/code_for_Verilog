#include <iostream>
#include <fstream>

void generateKaratsubaVerilog(int N) {
std::ofstream verilogFile("karatsuba_multiplier.v");
verilogFile << "module sm(\n"
"            output reg [" << N + 2 << ":0] prod,\n"
"            input [" << int((N + 1) / 2) << ":0] a,\n"
"            input [" << int((N + 1) / 2) << ":0] b\n"
");\n"
"            reg [" << N + 2 << ":0] result = " << N + 3 << "'b0;\n"
"            reg [2:0] i;\n"
"\n"
"            always @(*)\n"
"            begin\n"
"                for(i=0;i<" << int((N + 1) / 2) + 1 << ";i=i+1)\n"
"                begin\n"
"                    if((b&(1<<<i))!=0)\n"
"                    begin\n"
"                        result = result+(a<<<i);\n"
"                    end\n"
"\n"
"                end\n"
"            prod = result;\n"
"          end\n"
"endmodule\n"
"\n"
"module karatsuba_multiplier (\n"
"  input [" << N - 1 << ":0] a,\n"
"  input [" << N - 1 << ":0] b,\n"
"  output reg [" << 2 * N - 1 << ":0] result\n"
");\n"
"\n"
"  reg [" << int((N + 1) / 2) << ":0] prev_parts_a, parts_a, prev_parts_b, parts_b, parts_a_extended, parts_b_extended;\n"
"  wire [" << N + 2 << ":0] prev_res, extd_res, cntr_res;\n"
"  reg [" << 2*N - 1 << ":0] ext1, ext2;\n"
"  always @(*) begin\n"
"    parts_a = a[" << N - 1 << ":" << int((N + 1) / 2) << "];\n"
"    prev_parts_a = a[" << int((N + 1) / 2) << ":0];\n"
"    parts_a_extended = parts_a + prev_parts_a;\n"
"    parts_b = b[" << N - 1 << ":" << int((N + 1) / 2) << "];\n"
"    prev_parts_b = b[" << int((N + 1) / 2) << ":0];\n"
"    parts_b_extended = parts_b + prev_parts_b;\n"
"  end\n"
"\n"
"  sm port0( .a(prev_parts_a), .b(prev_parts_b), .prod(prev_res));\n"
"  sm port1( .a(parts_a), .b(parts_b), .prod(cntr_res));\n"
"  sm port2( .a(parts_a_extended), .b(parts_b_extended), .prod(extd_res));\n"
"  always @(*) begin\n"
"    ext1 = extd_res - cntr_res - prev_res << " << int((N + 1) / 2) << ";\n"
"    ext2 = cntr_res << " << N << ";\n"
"  end\n"
"\n"
"  always @(*) begin\n"
"    result = {ext2 + ext1 + prev_res};\n"
"  end\n"
"endmodule\n"
"\n"
"module karatsuba_multiplier_tb;\n"
"  reg [" << N - 1 << ":0] a;\n"
"  reg [" << N - 1 << ":0] b;\n"
"  wire [" << 2 * N - 1 << ":0] result;\n"
"\n"
"  karatsuba_multiplier uut (\n"
"    .a(a),\n"
"    .b(b),\n"
"    .result(result)\n"
"    );\n"
"\n"
"  initial begin\n"
"    a = 8'b11001010;\n"
"    b = 8'b00000101;\n"
"\n"
"    #100;\n"
"\n"
"    $display(\"Input a: %d\", a);\n"
"    $display(\"Input b: %d\", b);\n"
"    #100;\n"
"    $display(\"Result: %d\", result);\n"
"    $finish;\n"
"  end\n"
"endmodule\n";
}


int main() {
    int N;
    std::cout << "Enter the value of N: ";
    std::cin >> N;
    generateKaratsubaVerilog(N);
    std::cout << "Verilog files generated successfully.\n";

    return 0;
}
