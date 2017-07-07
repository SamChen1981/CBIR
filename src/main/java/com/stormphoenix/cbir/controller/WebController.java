package com.stormphoenix.cbir.controller;

import com.stormphoenix.cbir.Utils;
import com.stormphoenix.cbir.entities.HsiFeatureEntity;
import com.stormphoenix.cbir.entities.HuFeatureEntity;
import com.stormphoenix.cbir.entities.ImagesEntity;
import com.stormphoenix.cbir.entities.TextureFeatureEntity;
import com.stormphoenix.cbir.opencv.HsiFeature;
import com.stormphoenix.cbir.opencv.HuFeature;
import com.stormphoenix.cbir.opencv.TextureFeature;
import com.stormphoenix.cbir.reporsitory.JpaHsiFeature;
import com.stormphoenix.cbir.reporsitory.JpaImages;
import com.stormphoenix.cbir.reporsitory.JpaShapeFeature;
import com.stormphoenix.cbir.reporsitory.JpaTextureFeature;
import com.stormphoenix.cbir.structs.DistIdEntry;
import com.stormphoenix.cbir.structs.HsiCenterMatrix;
import com.stormphoenix.cbir.structs.ShapeHuMatrix;
import com.stormphoenix.cbir.structs.Texture;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.multipart.MultipartFile;
import org.springframework.web.servlet.mvc.support.RedirectAttributes;

import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.io.*;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.List;
import java.util.PriorityQueue;

/**
 * Created by Developer on 17-7-5.
 */
@Controller
public class WebController {
    @Autowired
    public JpaImages jpaImages;
    @Autowired
    public JpaHsiFeature jpaHsiFeature;
    @Autowired
    public JpaTextureFeature jpaTextureFeature;
    @Autowired
    public JpaShapeFeature jpaShapeFeature;

    @RequestMapping("/data_image")
    public void showDatabaseImage(@RequestParam("imageId") String imageId, HttpServletResponse response) {
        Integer id = Integer.parseInt(imageId);
        ImagesEntity imagesEntity = jpaImages.findById(id);
        File image = new File(imagesEntity.getPath());
        if (!image.exists()) {
            return;
        }
        try {
            FileInputStream fis = new FileInputStream(image);
            OutputStream oos = null;
            int c;
            while ((c = fis.read()) != -1) {
                oos = response.getOutputStream();
                oos.write(c);
            }
            oos.flush();
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    @RequestMapping("/uploaded_image")
    public void showUploadImage(HttpSession session, HttpServletResponse response) {
        String filename = (String) session.getAttribute("filename");
        if (filename == null) {
            return;
        }
        File image = new File(UPLOADED_FOLDER + File.separator + filename);
        if (!image.exists()) {
            return;
        }
        try {
            FileInputStream fis = new FileInputStream(image);
            OutputStream oos = null;
            int c;
            while ((c = fis.read()) != -1) {
                oos = response.getOutputStream();
                oos.write(c);
            }
            oos.flush();
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    //  Save the uploaded file to this folder
    private static String UPLOADED_FOLDER = "/home/Developer/Workspace/image_test";

    @GetMapping("/hsi_feature")
    public String hsiFeature(HttpSession session) {
        String filename = (String) session.getAttribute("filename");
        if (filename == null) {
//            System.out.println("jni failed .... null");
            return "redirect:/";
        }
        PriorityQueue<DistIdEntry> queue = new PriorityQueue<>();
        List<List<Integer>> imgRows = new ArrayList();
        int curImgId = 1;
        HsiCenterMatrix matrixR = HsiFeature.calculateHsiCenterMatrix(UPLOADED_FOLDER + File.separator + filename, 0);
        HsiCenterMatrix matrixG = HsiFeature.calculateHsiCenterMatrix(UPLOADED_FOLDER + File.separator + filename, 1);
        HsiCenterMatrix matrixB = HsiFeature.calculateHsiCenterMatrix(UPLOADED_FOLDER + File.separator + filename, 2);

        while (curImgId <= 9000) {
            HsiFeatureEntity hsiFeatureEntity = jpaHsiFeature.findByForeignKey(curImgId);
            double distance = HsiFeature.calculateHsiDistance(matrixR, matrixG, matrixB, hsiFeatureEntity);
            queue.add(new DistIdEntry(distance, curImgId));
            curImgId++;
        }

        imgRows = Utils.getShowingImageLists(queue);
        session.setAttribute("compared_images_result", imgRows);
        System.out.println("finish");
        return "redirect:/";
    }

    @GetMapping("/idm")
    public String idm(HttpSession session) {
        String filename = (String) session.getAttribute("filename");
        if (filename == null) {
//            System.out.println("jni failed .... null");
            return "redirect:/";
        }
        PriorityQueue<DistIdEntry> queue = new PriorityQueue<>();
        int curImgId = 1;

        Texture textureFeature = TextureFeature.calculateTextureFeature(UPLOADED_FOLDER + File.separator + filename);

        while (curImgId <= 9000) {
            TextureFeatureEntity textureFeatureEntity = jpaTextureFeature.findByForeignKey(curImgId);
            double distance = TextureFeature.calculateIdmDistance(textureFeature, textureFeatureEntity);
            queue.add(new DistIdEntry(distance, curImgId));
            curImgId++;
        }

        List<List<Integer>> imgRows = Utils.getShowingImageLists(queue);
        session.setAttribute("compared_images_result", imgRows);
        System.out.println("finish");
        return "redirect:/";
    }

    @GetMapping("/entropy")
    public String entropy(HttpSession session) {
        String filename = (String) session.getAttribute("filename");
        if (filename == null) {
//            System.out.println("jni failed .... null");
            return "redirect:/";
        }
        PriorityQueue<DistIdEntry> queue = new PriorityQueue<>();
        int curImgId = 1;

        Texture textureFeature = TextureFeature.calculateTextureFeature(UPLOADED_FOLDER + File.separator + filename);

        while (curImgId <= 9000) {
            TextureFeatureEntity textureFeatureEntity = jpaTextureFeature.findByForeignKey(curImgId);
            double distance = TextureFeature.calculateEntropyDistance(textureFeature, textureFeatureEntity);
            queue.add(new DistIdEntry(distance, curImgId));
            curImgId++;
        }

        List<List<Integer>> imgRows = Utils.getShowingImageLists(queue);
        session.setAttribute("compared_images_result", imgRows);
        System.out.println("finish");
        return "redirect:/";
    }

    @GetMapping("/texture_feature")
    public String textureFeature(HttpSession session) {
        String filename = (String) session.getAttribute("filename");
        if (filename == null) {
//            System.out.println("jni failed .... null");
            return "redirect:/";
        }
        PriorityQueue<DistIdEntry> queue = new PriorityQueue<>();
        int curImgId = 1;

        Texture textureFeature = TextureFeature.calculateTextureFeature(UPLOADED_FOLDER + File.separator + filename);

        while (curImgId <= 9000) {
            TextureFeatureEntity textureFeatureEntity = jpaTextureFeature.findByForeignKey(curImgId);
            double distance = TextureFeature.calculateTextureDistance(textureFeature, textureFeatureEntity);
            queue.add(new DistIdEntry(distance, curImgId));
            curImgId++;
        }

        List<List<Integer>> imgRows = Utils.getShowingImageLists(queue);
        session.setAttribute("compared_images_result", imgRows);
        System.out.println("finish");
        return "redirect:/";
    }

    @GetMapping("/shape_feature")
    public String shapeFeature(HttpSession session) {
        String filename = (String) session.getAttribute("filename");
        if (filename == null) {
//            System.out.println("jni failed .... null");
            return "redirect:/";
        }
        PriorityQueue<DistIdEntry> queue = new PriorityQueue<>();
        int curImgId = 1;

        ShapeHuMatrix shapeHuMatrix = HuFeature.calculateShapeHuFeature(UPLOADED_FOLDER + File.separator + filename);

        while (curImgId <= 9000) {
            HuFeatureEntity huFeatureEntity = jpaShapeFeature.findByForeignKey(curImgId);
            double distance = HuFeature.calculateHuMatrixDistance(shapeHuMatrix, huFeatureEntity);
            queue.add(new DistIdEntry(distance, curImgId));
            curImgId++;
        }

        List<List<Integer>> imgRows = Utils.getShowingImageLists(queue);
        session.setAttribute("compared_images_result", imgRows);
        System.out.println("finish");
        return "redirect:/";
    }

    @PostMapping("/upload")
    public String singleFileUpload(@RequestParam("file") MultipartFile file, HttpSession session,
                                   RedirectAttributes redirectAttributes) {
        if (file.isEmpty()) {
            redirectAttributes.addFlashAttribute("message", "Please select a file to upload");
            return "redirect:uploadStatus";
        }

        try {
            // Get the file and save it somewhere
            byte[] bytes = file.getBytes();
            Path path = Paths.get(UPLOADED_FOLDER + File.separator + file.getOriginalFilename());
            Files.write(path, bytes);

            session.setAttribute("filename", file.getOriginalFilename());
            redirectAttributes.addFlashAttribute("message",
                    "You successfully uploaded '" + file.getOriginalFilename() + "'");
        } catch (IOException e) {
            e.printStackTrace();
        }
        return "redirect:/";
    }

    @GetMapping("/uploadStatus")
    public String uploadStatus() {
        return "uploadStatus";
    }

    @RequestMapping("/")
    public String welcome() {
        return "welcome";
    }
}
