#include "gui.h"
#include "imgui.h"
#include "ogl.h"
#include <string>


bool save_window = false;
char save_input_text[255] = "";

void init_gui(GLFWwindow *window) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();
    ImGui::StyleColorsDark();
}


void gui_save_view() {
    if(save_window) {

        float pos_x = ( (float)g_get_screen_w() / 100 ) * 20;
        float pos_y = ( (float)g_get_screen_h() / 100 ) * 35;

        float size_w = ( (float)g_get_screen_w() / 100 ) * 40;
        float size_h = ( (float)g_get_screen_h() / 100 ) * 10;

        ImGui::SetNextWindowPos(ImVec2(pos_x,pos_y));
        ImGui::SetNextWindowSize(ImVec2(size_w,size_h));

        if(ImGui::Begin("Export",0,ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings)) {
            ImGui::InputText("",save_input_text,IM_ARRAYSIZE(save_input_text));
            ImGui::SameLine();
            if(ImGui::Button("ULOZIT"))
            {
                save_window = false;
                export_image(save_input_text);
                return;
            }
            ImGui::SameLine();
            if(ImGui::Button("ZRUSIT"))
            {
                save_window = false;
            }

            ImGui::End();
        }
    }
}

void gui_main_menu() {
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("Export"))
        {
            if (ImGui::MenuItem("Aktual")) 
            {
                save_window = true;
//                export_image("test");
            }
            if (ImGui::MenuItem("Vsetky")) 
            {
            }

            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}

void gui_fbo_view() {
    ImGui::SetNextWindowPos(ImVec2(0,19));

    float size_w = ( (float)g_get_screen_w() / 100 ) * 80;
    ImGui::SetNextWindowSize(ImVec2(size_w,g_get_screen_h() - 19));

    if(ImGui::Begin("FBO_RENDER",0,ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBringToFrontOnFocus  )) {
        if(ImGui::BeginTabBar("Main"))
        {
            if (ImGui::BeginTabItem("Tab"))
            {
                string fps="FPS ";
                ImGui::BeginChild("RENDER");
                ImVec2 size= ImGui::GetWindowSize();
                unsigned int t_id=g_get_main_buffer()->texture;
                ImGui::Image((ImTextureID)t_id,size,ImVec2(0,1),ImVec2(1,0));
                ImGui::EndChild();

                ImGui::EndTabItem();
            }
            ImGui::EndTabBar();
        }
        ImGui::End();
    }

}

void gui_side_panel() {

    float size_w = ( (float)g_get_screen_w() / 100) * 20 ;
    float pos_w = ( (float)g_get_screen_w() / 100) * 80;

    ImGui::SetNextWindowPos(ImVec2(pos_w,19));
    ImGui::SetNextWindowSize(ImVec2(size_w,g_get_screen_h() - 19));


    if(ImGui::Begin("BRUH",0,ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBringToFrontOnFocus  )) {
    //if(ImGui::Begin("BRUH")) {
        ImGui::Text("CAW");
        ImGui::SameLine();
        if(ImGui::Button("SAVE"))
        {
            return;
        }
        ImGui::SameLine();
        if(ImGui::Button("CANCEL"))
        {
        }

        ImGui::End();
    }
}


void draw_gui() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    gui_main_menu();
    gui_fbo_view();
    gui_side_panel();
    gui_save_view();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
